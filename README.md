## Build Steps

Run the following:
```
mkdir build && cd build
```

Then
```
cmake ..
```

Finally
```
make
```

This will create binaries ```q1```, and ```q2```. Run them.


```
./q1
```
This will crack whatever is in ```q1.txt``` and print results.
Logs will be written to ```./build/q1log.txt```. If you don't see anything printed to stdout for a while, check the log file for progress.


```
./q2
```

This will crack whatever is in ```q2.txt``` and print results.
Logs will be written to ```./build/q2log.txt```. If you don't see anything printed to stdout for a while, check the log file for progress.