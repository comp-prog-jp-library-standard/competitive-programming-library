# Contribution Guide
このプロジェクトに貢献したいと思ってくださり、ありがとうございます。

## 議論について
以下の場所で議論をしています。

- この GitHub プロジェクトの [issue](https://github.com/comp-prog-jp-library-standard/competitive-programming-library/issues)
- 競プロ Slack ([https://competitiveprogramming.info/slack](https://competitiveprogramming.info/slack)) の #library-standard チャンネル


## Issue
バグ報告・欲しいライブラリ・機能追加など、歓迎しています。
 [新しい Issue を作る](https://github.com/comp-prog-jp-library-standard/competitive-programming-library/issues/new)
## Pull Request
以下のような pull request を歓迎しています。

- 新しいアルゴリズムの追加
- 新しいテストの追加
- 既存のライブラリ・テストコードのバグ修正・改善
- ドキュメントの加筆・修正

Pull request を送るべきか迷った場合は、 issue を立てて相談してみてください。
実際に開発を行う際には、wiki の[開発の流れ](https://github.com/comp-prog-jp-library-standard/competitive-programming-library/wiki/%E9%96%8B%E7%99%BA%E3%81%AE%E6%B5%81%E3%82%8C)を参考にしてください。


### Pull Request を送っていただく前に

ローカルで以下のことが成り立つかどうか確かめてください:

- ライブラリ用のコード本体は `src/` 以下に、テスト用のコードは `test/` 以下にある
- `bin/travis-test.sh` を実行して `OK` という文字列が表示される

`bin/travis-test.sh` は内部で `clang-format` を実行するため、あらかじめインストールしておく必要があります。([開発環境](https://github.com/comp-prog-jp-library-standard/competitive-programming-library/wiki/%E9%96%8B%E7%99%BA%E7%92%B0%E5%A2%83))
