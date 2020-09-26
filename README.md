# my_benchmark_template
## 简介
使用google/benchmark的示例来做的性能测试的框架, 暂时只支持MSVC2019.

## 编译
> mkdir build
>
> cd build
>
> cmake ..
>
> MSBuild.exe my_benchmakr_template.sln -p:Configuration=Release  -t:Rebuild

## 运行
> cd build\Release
>
> .\my_benchmark_template.exe