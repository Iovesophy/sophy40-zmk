---
inclusion: always
---

# ZMKキーボード開発ワークフロー

## 重要：マトリックス定義の前に必ずArduinoでテストする

ZMKの設定を始める前に、必ずArduinoでマトリックススキャンを実行してください。

### 1. ハードウェアの確認

- はんだ付けの確認（特にマイコンのピン）
- スイッチの動作確認
- ダイオードの向きと導通確認
- ホットスワップソケットの確認

### 2. Arduinoでマトリックススキャン

**重要：XIAO nRF52840ではI2Cを無効化する**

```cpp
#include <Wire.h>

const int rowPins[] = {D2, D3, D4, D5};  // 使用するRowピン
const int colPins[] = {D10, D9, D8, D7, D0, D1};  // 使用するColピン

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  // I2Cを無効化（D5=SDA, D8=SCKを使う場合は必須）
  Wire.end();
  
  Serial.println("Matrix Scanner");
  
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  for (int i = 0; i < 6; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  for (int row = 0; row < 4; row++) {
    digitalWrite(rowPins[row], LOW);
    delayMicroseconds(50);
    
    for (int col = 0; col < 6; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        Serial.print("Row");
        Serial.print(row);
        Serial.print(" Col");
        Serial.println(col);
        delay(300);
      }
    }
    
    digitalWrite(rowPins[row], HIGH);
  }
  delay(10);
}
```

### 3. 全キーを順番にテスト

左上から順番に、1段ずつ全てのキーを押して、Row/Col番号を記録する。

### 4. ZMKのマトリックスマッピングを作成

Arduinoのテスト結果を元に、`sophy40.dtsi` の `map` を定義する。

### 5. ZMKでI2Cを無効化

`sophy40.dtsi` に以下を追加：

```
&xiao_i2c {
    status = "disabled";
};
```

### 6. ピン定義

XIAO nRF52840では `&xiao_d` 表記を使用：

```
row-gpios = <&xiao_d 2 ...>, <&xiao_d 3 ...>, <&xiao_d 4 ...>, <&xiao_d 5 ...>;
col-gpios = <&xiao_d 10 ...>, <&xiao_d 9 ...>, ...;
```

### トラブルシューティング

- **キーが反応しない**：はんだ付け、ソケット、ダイオードを確認
- **マッピングがずれる**：Arduinoで再テスト
- **I2Cピンが動作しない**：`Wire.end()` または `&xiao_i2c { status = "disabled"; }` を確認

### 7. ボード名とビルド設定

**重要：XIAO nRF52840の正しいボード名**

GitHub Actionsワークフローファイル（`.github/workflows/build.yml`）では、必ず以下のボード名を使用する：

```yaml
# 正しいボード名
-b xiao_ble

# 間違ったボード名（使用禁止）
-b seeeduino_xiao_ble  # 古い名前、エラーの原因
```

**ワークフローファイルの正しい設定例：**

```yaml
- name: West Build (Left)
  run: west build --pristine -s zmk/app -b xiao_ble -- -DSHIELD=sophy40_left -DZMK_CONFIG="${GITHUB_WORKSPACE}/config"

- name: West Build (Right)  
  run: west build --pristine -s zmk/app -b xiao_ble -- -DSHIELD=sophy40_right -DZMK_CONFIG="${GITHUB_WORKSPACE}/config"
```

### 8. プッシュ前の最終確認プロセス

**重要：必ずプッシュ前に以下を確認する**

#### 最終確認チェックリスト

1. **キーマップファイルの確認**
   ```bash
   # ファイル内容を確認
   cat config/sophy40.keymap
   ```

2. **レイヤー構成の確認**
   - デフォルトレイヤー（0）: 基本QWERTY配列
   - 数字レイヤー（1）: 数字・記号・Vimナビゲーション
   - その他のレイヤー: 必要に応じて

3. **タップダンス設定の確認**
   - ENキー: `LANG2` / 数字レイヤー切り替え
   - 右スペース: `SPACE` / 数字レイヤー切り替え
   - その他のタップダンス

4. **Combo設定の確認**
   - Fnキー + QWERTYキーの組み合わせ
   - 記号入力の正確性

5. **構文エラーのチェック**
   ```bash
   # 構文エラーがないか確認
   git add config/sophy40.keymap
   git status
   ```

6. **コミット前の最終レビュー**
   - 変更内容の説明を明確に記述
   - 意図しない変更が含まれていないか確認

7. **プッシュ実行**
   ```bash
   git commit -m "明確な変更内容の説明"
   git push
   ```

#### プッシュ後の確認

- GitHub Actionsでビルドが成功することを確認
- エラーが発生した場合は即座に修正

### 注意事項

- ネットリストだけでは不十分。実際の配線を確認する。
- テスターで導通確認しても、Arduinoで反応しない場合がある（I2C、ソケット不良など）。
- 必ず全キーをテストしてから、ZMKの設定を開始する。
- **ボード名は絶対に `xiao_ble` を使用する**。他の名前はビルドエラーの原因となる。
- ZMKのバージョンは `main` ブランチを使用（`config/west.yml`）。
- **プッシュ前は必ず最終確認プロセスを実行する**。
