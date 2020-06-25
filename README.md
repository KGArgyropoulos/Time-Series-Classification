# Time-Series-Classification

This is a data mining and machine learning-related project, written in C programming language.\
The main object of this project is time series classification, applying the dynamic time warping algorithm, to measure the similarity of two time series.

# Time-Series Theory

[WikiLink] (https://en.wikipedia.org/wiki/Time_series)

Let two time series A and B, with ai(1<=n<=N) and bj(1<=n<=N).\
Ai is the time series including the i-first elements of A.\
Bj is the time series including the j-first elements of B.\
DTW distance of the two timeseries (dtw(Ai,Bj)), \
given that \
![alt text](https://github.com/KGArgyropoulos/Time-Series-Classification/blob/master/images/img3.png)
equals: \
![alt text](https://github.com/KGArgyropoulos/Time-Series-Classification/blob/master/images/img1.png)
So DTW distance between A and B equals: \
![alt text](https://github.com/KGArgyropoulos/Time-Series-Classification/blob/master/images/img2.png)

