# Parallel Task Scheduling

## Table of contents

  - [General info](#general-info)
  - [Technologies](#technologies)
  - [Setup](#setup)

## General info
The purpose of parallel task scheduling is to minimize total processing time of given tasks by adequately assigning them to available processors. Time limit intended for finding a solution is set to 5 minutes. The input to a program is a swf file, which contains information about tasks, such as time of arrival to a system, processing time and required number of processors. Tasks are unsplittable and the allocation of processors is contiguous. Having such data, program must find near to optimal solution, by first applying greedy algorithm and then mutating an input list and doing local search. This effects in building better solutions as time goes by. The biggest challenge was in upgrading speed of the program, especially because there can be input instances, which vary in processing times of tasks and number of tasks. 

## Technologies
C++

## Setup
1. You must have gcc compiler for Linux installed.
2. Open Linux terminal.
3. Download swf input file from https://www.cs.huji.ac.il/labs/parallel/workload/
4. Create swf output file.
5. To compile, type `make`.
6. To run program and measure time, write: 
   
    `time ./main name_in.swf name_out.swf 10000`

    name_in.swf is an input file

    name_out.swf is an output file

    10000 is sample number of tasks which we want to read from the file
