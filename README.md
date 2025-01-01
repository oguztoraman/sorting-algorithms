# Sorting Algorithms

A C++20 program to compare sorting algorithms with command line user interface.

## Requirements

+ git
+ g++ version >= 10
+ cmake version >= 3.14
+ [boost program options](https://www.boost.org/)

## Installing Requirements

> For Fedora

```
sudo dnf install cmake make g++ git boost-program-options
```


## Installation

1. clone 
```
git clone https://github.com/oguztoraman/sorting-algorithms
```

2. build 
```
cd sorting-algorithms && cmake . && make
```

3. run
```
./sorting-algorithms -h
```

## Sample Outputs
```
./sorting-algorithms -h
sorting-algorithms
A C++20 program to compare sorting algorithms.

Usage: sorting-algorithms [OPTION]...:
  -h [ --help ]            display this help message
  -v [ --version ]         display version
  --input-size arg (=5000) the number of randomly generated inputs to be sorted
  --input-file arg         read inputs from a file
  --test-count arg (=21)   how many times to perform sorting per algorithm
  --generate arg           the number of files each containing randomly 
                           generated inputs

sorting-algorithms v1.0.1
https://github.com/oguztoraman/sorting-algorithms

Copyright Oğuz Toraman 2022-2024.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

Written by Oğuz Toraman, oguz.toraman@tutanota.com
```
---
```
./sorting-algorithms
sorting algorithms are comparing for 5'000 inputs, each sorting is performing 21 times per algorithm, please wait...
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
|  algorithm  |   input size   |  # of tests  |  # of comparisons   |  # of assignments   |     median time(~)      |     average time(~)     |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  selection  |          5'000 |           21 |              35'465 |               9'998 |    0m  0s  52ms 958us   |    0m  0s  54ms 763us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    buble    |          5'000 |           21 |           6'245'339 |          12'490'678 |    0m  0s 163ms 896us   |    0m  0s 167ms 444us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    quick    |          5'000 |           21 |              37'318 |              81'290 |    0m  0s   1ms   3us   |    0m  0s   1ms   5us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    merge    |          5'000 |           21 |              55'242 |              61'808 |    0m  0s   2ms 852us   |    0m  0s   2ms 855us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  insertion  |          5'000 |           21 |           6'245'339 |           6'250'338 |    0m  0s  42ms 727us   |    0m  0s  43ms 414us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    heap     |          5'000 |           21 |              75'699 |             114'408 |    0m  0s   1ms 735us   |    0m  0s   1ms 728us   |
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
```
---
```
./sorting-algorithms --generate=5 --input-size=1000
generating 5 files, each containing 1'000 random inputs, please wait...
generated 5 files, each containing 1'000 random inputs.
```
---
```
./sorting-algorithms --input-file=input1.txt --test-count=5
sorting algorithms are comparing for 1'000 inputs, each sorting is performing 5 times per algorithm, please wait...
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
|  algorithm  |   input size   |  # of tests  |  # of comparisons   |  # of assignments   |     median time(~)      |     average time(~)     |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  selection  |          1'000 |            5 |               5'380 |               1'998 |    0m  0s   2ms 355us   |    0m  0s   2ms 349us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    buble    |          1'000 |            5 |             245'820 |             491'640 |    0m  0s   7ms 357us   |    0m  0s   7ms 798us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    quick    |          1'000 |            5 |               5'040 |              11'422 |    0m  0s   0ms 153us   |    0m  0s   0ms 153us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    merge    |          1'000 |            5 |               8'707 |               9'976 |    0m  0s   0ms 538us   |    0m  0s   0ms 532us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  insertion  |          1'000 |            5 |             245'820 |             246'819 |    0m  0s   1ms 818us   |    0m  0s   1ms 843us   |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    heap     |          1'000 |            5 |              11'660 |              18'122 |    0m  0s   0ms 296us   |    0m  0s   0ms 299us   |
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
```
---
```
./sorting-algorithms -v
sorting-algorithms v1.0.1
https://github.com/oguztoraman/sorting-algorithms

Copyright Oğuz Toraman 2022-2025.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

Written by Oğuz Toraman, oguz.toraman@tutanota.com
```

## License

Boost Software License - Version 1.0, see [LICENSE_1_0.txt](https://github.com/oguztoraman/sorting-algorithms/blob/main/LICENSE_1_0.txt) file for details.

### To Do
+ [ ] Update the CMakeLists.txt file.