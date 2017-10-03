# Demultiplex

This is the source code of the C++ program for demultiplexing the mRNA-sequencing data files (in FASTQ format) obtained by the 3'-end digital gene expression (3'-DGE) technology.

To compile the source code, open a terminal console and change current directory to the top directory of the source code tree, and then issue the following command:

*In Unix-alike systems (e.g. Linux and MacOS):*

```bash
g++ -Wall -std=c++1z -I "${SRC_FILE_DIR}" -O3 -o "${BIN_FILE}" $(find "${SRC_FILE_DIR}" -type f -name "*cpp")
```

*In Windows system:*

```bat
cl /std:c++17 /EHsc /Ox /I%SRC_FILE_DIR% /Fe%BIN_FILE% main.cpp hts\*cpp utk\*cpp
```

where, `${SRC_FILE_DIR}` or `%SRC_FILE_DIR%` is the top directory of the source code tree, and `${BIN_FILE}` or `%BIN_FILE%` is the executable file to generate.

Note: the source code must be compiled by the C++ compilers that supports the C++17 standard, such as GCC 7.0, Clang 3.9, Visual Studio 2017, or newer.
