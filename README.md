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
q1 should take less than 5 seconds.


```
./q2
```

This will crack whatever is in ```q2.txt``` and print results.
q2 is harder to crack and runing it is expensive. It launches 20 threads to do the computation. For my example one run could take 3 - 5 minutes.