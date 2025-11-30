# ZMK Firmware Configuration

このリポジトリは、ZMK Firmwareを使用したキーボード設定です。

## ビルド方法

このリポジトリをGitHubにプッシュすると、GitHub Actionsが自動的にファームウェアをビルドします。

1. このリポジトリをGitHubにプッシュ
2. Actionsタブでビルドの進行状況を確認
3. ビルドが完了したら、Artifactsからファームウェア（.uf2ファイル）をダウンロード

## ファームウェアの書き込み

1. キーボードをリセットモードにする（RESETボタンを2回押す）
2. マスストレージデバイスとして認識される
3. ダウンロードした.uf2ファイルをドラッグ&ドロップ
4. 自動的に再起動して完了

## キーマップのカスタマイズ

`config/corne.keymap` ファイルを編集してキーマップをカスタマイズできます。

### レイヤー構成

- **Layer 0 (Default)**: 基本的なQWERTY配列
- **Layer 1 (Lower)**: 数字、矢印キー、Bluetooth設定
- **Layer 2 (Raise)**: 記号キー

## 設定ファイル

- `config/corne.keymap`: キーマップ定義
- `config/corne.conf`: キーボード設定（Bluetooth、スリープなど）
- `config/west.yml`: ZMKのバージョン管理

## 対応ボード

現在の設定は以下のボードに対応しています：
- nice!nano v2

別のボードを使用する場合は、`.github/workflows/build.yml` の `-b` オプションを変更してください。

## 参考リンク

- [ZMK Documentation](https://zmk.dev/)
- [ZMK Keycodes](https://zmk.dev/docs/codes)
- [ZMK Behaviors](https://zmk.dev/docs/behaviors)
