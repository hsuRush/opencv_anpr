 ## It's an opencv anpr project  (only OCR part)
>```using KNN and can be able to train back.```

 There's two way to use
> ```make your own sample (xml files) ```<br>
>``` use origin xmls files ```

### Make your's sample
#### if you want to make your own sample (xml files) , make sure that the samples files path is avaible to yours .

```cpp
string traindata_address = "....."
```

#### Then unannotate  fs save part in the first time! 
```cpp
//////File save 
```
#### the pushback value from classtication need to be edited (depend on your picture) and simultaneously pushback to the image (the order can't be wrong) 

##### after running ,  remember annotate it.
### `Running with existed xmls file`
#### if you want to use mine just run it.

#### remember to annotate it the code  from

```cpp
 /*
    ////using trainingdata
    Mat traindata [36];
```
#### to 
```cpp
//////File save 
```

## How to Train the KNN model
### The program will ask user if it is correct or not 
>### if no , type the right one and will be written into xmls files
>### if yes, automatically written into xml files 


