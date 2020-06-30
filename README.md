## BloomFilter
A probabilistic data structure for efficiently querying membership test 

## Usage
Run the following commands to build and run bloomfilter 
```
$ cmake .
$ make
$ ./bloom
```

## Current Features
1. Create
2. Query

## TODO
1. Insert
2. Allow variable parameters k, m, and err (false probability rate)
3. Command line utility that:
    1. loads from file
    2. create and save bloom-filter on disk
    3. allow querying this bloom-filter-file
     
    