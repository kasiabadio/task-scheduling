all: 
	g++ -O3 main.cpp processor.cpp read_config.cpp job.cpp greedy.cpp write_config.cpp input_change.cpp -o main

clean:
	rm main.exe