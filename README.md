# pluginlib
ROSのpluginlibライクなプラグインライブラリ

# ビルド&実行方法
```shell
mkdir build
cd build
cmake ..
make
make install #これを忘れないこと
cd bin
./main
```

# やりたいこと

プラグインとして、クラスに対する実装を動的に追加したい。  

クラスの継承の使い方として、以下のようなものがある。
```cpp
class SampleBaseClass{
  virtual ~SampleBaseClass(){}
  virtual void exec(){}
};

class SampleClass1 : public SampleBaseClass{
  void exec(){std::cout<<"class2"<<std::endl;}
};


class SampleClass2 : public SampleBaseClass{
  void exec(){std::cout<<"class2"<<std::endl;}
};

void main(){
  SampleClass1 s1;
  SampleClass2 s2;
  std::vector<SampleBaseClass> s_vec;
  v.push_back(s1);
  v.push_back(s2);
  
  for(auto s:s_vec)
  {
     s.exec();
  }
}
```

ここで、新しいクラスSampleClass3を追加しようとすると、このソースコードをコンパイルし直さなければならない。  
それを、プラグインとして追加できるようにして、メインの実装はコンパイルし直さなくて良くするというのが、やりたいことである。

# ディレクトリ構成
```
| - src : プラグインライブラリのソース  
| - examples :　プラグインライブラリを使ったサンプルソース  
　　　 | - main : ベースクラスを使った共通処理を行う。上記、メイン文に相当  
      | - plugin_interface : プラグインのベースクラス。上記、SampleBaseClassに相当  
      | - plugin : プラグインとして動的リンク可能な、派生クラス。上記、SampleClass1などに相当
```

# サンプルソース説明

## ベースクラス部(plugin_interface)
まずは、メイン処理から利用する、全プラグイン実装に共通のクラスを定義する。

example/plugin_interface/sample_plugin_interface.hpp
```cpp
#include "plugin_loader.hpp" // これが必要

class SamplePluginInterface{
public:
    typedef std::shared_ptr<SamplePluginInterface> Ptr;

    //std::shared_ptrを利用しているので、アプリが終了するまで開放されないようにするために、ハンドラが必要)
    SamplePluginInterface(Handler handler = nullptr):handler(handler){
    }

    virtual ~SamplePluginInterface(){}

    Handler getHandler(){
        return handler;
    }

　　 //メイン処理から呼び出す、共通関数
    virtual void init(){};
    virtual void exec() = 0;

private:
    Handler handler;

};
```

## プラグイン部(plugin)
プラグイン部分は、ソースコードと設定ファイルが必要である。

### ソースコード
次に、ベースクラスから派生したクラスを定義する。  
これは、メイン処理とは別にコンパイルして、動的ライブラリ化する。  

example/plugin/sample_plugin.hpp
```cpp
#include "plugin_exporter.hpp"

class SamplePlugin: public SamplePluginInterface {
public:
    SamplePlugin(Handler handler) :
            SamplePluginInterface(handler) {
    }

    ~SamplePlugin() {
    }


    void exec(){
        std::cout<<"Hello World."<<std::endl;
    }

};

//これが、必要
PLUGIN_EXPORT_CLASS(SamplePlugin, SamplePluginInterface);
```

ここで、PLUGIN_EXPORT_CLASSというのは、下記のような関数を作成するマクロである。
このマクロは、下記で説明する設定ファイルから特定されて、呼び出される。
```cpp
SamplePluginInterface* SamplePluginFactory(Handler handler)
{
  new SamplePlugin(handler);
}
```


### 設定ファイル
以下のような設定ファイルを作成する  
example/plugin/config/sample_plugin_info.json  
```json
{
    "name": "sample_plugin", <<動的ライブラリのファイル名
    "class": "SamplePlugin", <<派生クラスの名前
    "base_class": "SamplePluginInterface" <<ベースクラスの名前
}
```

このファイルに対して、プラグインライブラリは、以下のように処理する。  

1. この設定ファイルを読み込む
2. 読み込みたい対象のベースクラスかどうかをbase_classの文字列から確認する。
3. 読み込み対象のベースクラスであれば、対応する動的ライブラリ(lib[nameの文字列].so)を読み込む。
4. classの文字列のクラスのインスタンスを作成する([classの文字列]Factory関数を呼び出す)

## メイン処理(main)

このプラグインを利用するメイン処理は、以下のとおりである。
``` cpp
#include "sample_plugin_interface.hpp"
#include "plugin_list_loader.hpp"

//プラグインを読み込む関数を定義
using SamplePluginInterfaceList = PluginList<SamplePluginInterface>;
void loadPlugins(std::string plugin_dir,SamplePluginInterfaceList::Ptr panels);

void loadPlugins(std::string plugin_dir,SamplePluginInterfaceList::Ptr panels){
    //plugin_dirディレクトリ内にある設定ファイルを走査して、base_classが、SamplePluginInterfaceのものを読み込む
    loadPlugins<SamplePluginInterface>(plugin_dir,"SamplePluginInterface", panels);
}


int main(){
　　 SamplePluginInterfaceList::Ptr pluginList;
    pluginList = std::make_shared<SamplePluginInterfaceList>();
    
    //./ディレクトリから、設定ファイルを読み込んで、SamplePluginInterfaceがベースクラスのプラグインを、リストに格納する
    loadPlugins("./", pluginList);

　　//プラグインを使う
　　for(auto plugin:pluginList->getPlugins()){
        plugin->exec();
    }

    return 0;
}
```
