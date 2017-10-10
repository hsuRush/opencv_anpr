 ## It's an opencv anpr project
> ##### using KNN model and can be able to train back.
> ##### using post processing such as 
>- ##### GaussianBlur 
>- ##### GrayScale
>- ##### OTSU threshold
>- ##### Edge detection
>- ##### using slide window algorithm to implement the plate dectection

![Result](https://user-images.githubusercontent.com/22855741/31375962-d4e13444-add5-11e7-90bb-99b3a54224c5.png)

#### There's two methods to run it
>- ``` make your own sample xml files ```<br>
>- ``` use origin xmls files ```

### 1.Make your's sample
##### if you want to make your own sample xml files , make sure the samples files path is avaible.

```cpp
string traindata_address = "....."
```

##### Then remove the annotate on fs save part in the first time! 
```cpp
 /*
    ////using trainingdata
    Mat traindata [36];
```
##### to 
```cpp
//////File save 
```
##### the pushback value (sign) must match the picture, and need to be transfer to int type as well.Last,pushback the image data simultaneously.
##### after running it ,  remember annotate. <br><br><br><br>

### 2.Running with existed xmls file
##### if you want to use mine just run it.

##### remember to annotate  the code  from

```cpp
 /*
    ////using trainingdata
    Mat traindata [36];
```
##### to 
```cpp
//////File save 
```

### How to Train the KNN model and write it back ?
#### The program will ask user if it is correct or not 
>##### if no , type the right one and will be written into xmls files
>##### if yes, automatically write into xml files 


