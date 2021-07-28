# lecture-classical-raytracer-2021
For Ray Group's lecture in 2021. 
2021年度のレイ班の講義で使用するリポジトリです。

CMakeを使用するため、クローン後に

```
mkdir build
cd build
cmake ..
```

を行ってください。
また、cmakeの設定が終わった後、buildファイル内で

```
make
```
を行うことでビルドが開始します。そうするとmain.cppのコンパイル結果がbuildファイル内にmainという実行ファイルとして出ますので、実行はこのファイルから行ってください。

受講者の方はsrcフォルダ内のmain.cppを中心にプログラムを書いていってもらいます。
refフォルダは実装例を入れるフォルダであり、通常は上記のmakeでコンパイルされないようになっています。
refの実装例を実行したい場合、最上位ディレクトリにあるCMakeLists.txtの
```
option(BUILD_REFERENCE "build reference raytracer" OFF)
```
を以下のようにOFFからONにしてください。
```
option(BUILD_REFERENCE "build reference raytracer" ON)
```
これをした後、最初と同様cmakeコマンドをやり直して、makeをすればbuildフォルダの中にrefができますので、その中から行いたい実装例のファイル名を実行してください。