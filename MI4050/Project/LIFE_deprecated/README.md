# LIFE for MTS with missing values
This is an implementation of the `Learning Individual Features (LIFE)` approach for MTS with missing values. We provide PhysioNet dataset and the corresponding codes. The codes have been tested on Ubuntu 18.04 with single Nvidia TITAN Xp graphic card.

If our work is helpful to you, please kindly cite our paper:

	Zhao-Yu Zhang, Shao-Qun Zhang, Yuan Jiang, and Zhi-Hua Zhou. LIFE: Learning Individual Features for Multivariate Time Series Prediction with Missing Values. In: Proceedings of the 21st IEEE International Conference on Data Mining (ICDM'21), Auckland, New Zealand, 2021.

## ATTN
This package is free for academic usage. You can run it at your own risk. For other purposes, please contact Prof. Zhi-Hua Zhou (zhouzh@nju.edu.cn).

## ATTN2
This package was developed by Mr. Zhao-Yu Zhang (zhangzhaoyu@lamda.nju.edu.cn). For any problem concerning the code, please feel free to contact Mr. Zhang.

## Requirements
* `Python3` packages
	* dtaidistance>=1.2.3
	* numpy>=1.17.3
	* POT>=2.2.3
	* PyYAML>=5.1.2
	* scikit-learn>=0.21.3
	* seaborn>=0.10.1
	* sktime>=0.6.0
	* torch>=1.2.0
	* torchvision>=0.4.1
	* ujson>=3.0.0

## To run the models:
* preprocess the data 
	* `python data_process.py`
* run models 
    * `cd LIFE`
	* `python main.py`

## To extract correlation matrix:
* CME-PDTW as an example
    * `cd CME`
	* `python CME_PDTW.py`

