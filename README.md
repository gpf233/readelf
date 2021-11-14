# readelf

## usage:

```sh
# -h, -S, -l选项三选一，与系统库中readelf选项一致，分别对应解析elf header，解析section headers table, 解析program headers table。
bin/readelf <-h|-S|-l> elffile
```

## hierarchy:

```txt
readelf
├── bin
│   └── readelf
├── CMakeLists.txt
├── include
│   └── func.h
├── lib
│   └── libfunc.so
├── LICENSE
├── README.md
└── src
    ├── func.c
    └── main.c
```

### main.c

从`elf`文件中提取信息填充`Elf64_Ehdr`, `Elf64_Shdr`, `Elf64_Phdr`结构体。

### func.c

解析`main.c`中填充的三类结构体（基本全是`printf`）。

## 额外说明

1. 只做了64位的（32位与64位解析方法基本相同）。
2. 因为用到了`Elf64_Ehdr`, `Elf64_Shdr`, `Elf64_Phdr`这些结构体以及相关的类型定义，所以需要依赖`elf.h`头文件。
3. 输出格式与系统中的`readelf`基本相同。`Elf64_Ehdr`中没有与`elf header`解析结果中的`OS/ABI`和`ABI Version`与之对应的字段，故在解析结果中将这两条留空；`section header`和`program header`中的`type`和`flags`以十进制整数的形式输出，没有实现对应的`to_string`；三种数据结构中没有与`program headers table`解析结果中的`section`到`segment`的映射对应的字段，故这部分也留空。
4. 因为编译采用了动态链接的方式，所以`bin/readelf`可能不能在其他电脑上直接运行，需要用`cmake`重新编译。
