# Sorting Algorithms
A C++20 program to compare sorting algorithms with command line user interface

## Required Softwares
+ git
+ g++ version >= 10
+ cmake version >= 3.14

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

## Sample Output
```
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
|  algorithm  |   input size   |  # of tests  |   # of comparisons  |   # of assignments  |      median time(~)     |     average time(~)     |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  selection  |          5'000 |           21 |              34'407 |               9'998 |     0m  0s  91ms 191us  |     0m  0s  95ms 202us  |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    bubble   |          5'000 |           21 |           6'193'025 |          12'386'050 |     0m  0s 266ms  84us  |     0m  0s 267ms  52us  |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    quick    |          5'000 |           21 |              38'468 |              83'638 |     0m  0s   1ms 667us  |     0m  0s   1ms 703us  |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|    merge    |          5'000 |           21 |              55'144 |              61'808 |     0m  0s   5ms  74us  |     0m  0s   5ms 125us  |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|  insertion  |          5'000 |           21 |           6'193'025 |           6'198'024 |     0m  0s  72ms 726us  |     0m  0s  73ms 508us  |
|-------------|----------------|--------------|---------------------|---------------------|-------------------------|-------------------------|
|     heap    |          5'000 |           21 |              75'821 |             114'368 |     0m  0s   3ms  16us  |     0m  0s   3ms 114us  |
+-------------+----------------+--------------+---------------------+---------------------+-------------------------+-------------------------+
```

