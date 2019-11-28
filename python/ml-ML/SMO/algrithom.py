#SMO算法相关辅助中的辅助函数
#1 解析文本数据函数，提取每个样本的特征组成向量，添加到数据矩阵
#添加样本标签到标签向量
def loadDataSet(filename):
    dataMat=[];labelMat=[]
    fr=open(filename)
    for line in fr.readlines():
        lineArr=line.strip().split('\t')
        dataMat.append([float(lineArr[0]),float(lineArr[1])])
        labelMat.append((float()lineArr[2]))
    return dataMat,labelMat

#2 在样本集中采取随机选择的方法选取第二个不等于第一个alphai的
#优化向量alphaj
def selectJrand(i,m):
    j=i
    while(j==i):
        j=int(random.uniform(0,m))
    return j

#3 约束范围L<=alphaj<=H内的更新后的alphaj值    
def clipAlpha(aj,H,L):
    if aj>H:
        aj=H
    if L>aj：
        aj=L
    return aj

#SMO算法的伪代码
#创建一个alpha向量并将其初始化为0向量
#当迭代次数小于最大迭代次数时(w外循环)
    #对数据集中每个数据向量(内循环):
    #如果该数据向量可以被优化：
        #随机选择另外一个数据向量
        #同时优化这两个向量
        #如果两个向量都不能被优化，退出内循环
#如果所有向量都没有被优化，增加迭代次数，继续下一次循环

#@dataMat    ：数据列表
#@classLabels：标签列表
#@C          ：权衡因子（增加松弛因子而在目标优化函数中引入了惩罚项）
#@toler      ：容错率
#@maxIter    ：最大迭代次数
def smoSimple(dataMat,classLabels,C,toler,maxIter):
    #将列表形式转为矩阵或向量形式
    dataMatrix=mat(dataMatIn);labelMat=mat(classLabels).transpose()
    #初始化b=0，获取矩阵行列
    b=0;m,n=shape(dataMatrix)
    #新建一个m行1列的向量
    alphas=mat(zeros((m,1)))
    #迭代次数为0
    iter=0
    while(iter<maxIter):
        #改变的alpha对数
        alphaPairsChanged=0
        #遍历样本集中样本
        for i in range(m):
            #计算支持向量机算法的预测值
            fXi=float(multiply(alphas,labelMat).T*\
            (dataMatrix*dataMatrix[i,:].T))+b
            #计算预测值与实际值的误差
            Ei=fXi-float(labelMat[i])
            #如果不满足KKT条件，即labelMat[i]*fXi<1(labelMat[i]*fXi-1<-toler)
            #and alpha<C 或者labelMat[i]*fXi>1(labelMat[i]*fXi-1>toler)and alpha>0
            if((labelMat[i]*Ei<-toler)and(alpha<C))or\
            ((labelMat[i]*Ei>toler)and(alpha[i]>0))):
                #随机选择第二个变量alphaj
                j=selectJrand(i,m)
                #计算第二个变量对应数据的预测值
                fXj=float(multiply(alphas,labelMat).T*\
                    (dataMatrix*dataMatrix[j,:]).T)+b
                #计算与测试与实际值的差值
                Ej=fXj-float(label[j])
                #记录alphai和alphaj的原始值，便于后续的比较
                alphaIold=alphas[i].copy()
                alphaJold=alphas[j].copy()
                #如何两个alpha对应样本的标签不相同
                if(labelMat[i]!=labelMat[j]):
                    #求出相应的上下边界
                    L=max(0,alphas[j]-alphas[i])
                    H=min(C,C+alphas[j]-alphas[i])
                else:
                    L=max(0,alphas[j]+alphas[i]-C)
                    H=min(C,alphas[j]+alphas[i])
                if L==H:
                    print("L==H");continue

                #根据公式计算未经剪辑的alphaj
                #------------------------------------------
                eta=2.0*dataMatrix[i,:]*dataMatrix[j,:].T-\
                    dataMatrix[i,:]*dataMatrix[i,:].T-\
                    dataMatrix[j,:]*dataMatrix[j,:].T
                #如果eta>=0,跳出本次循环
                if eta>=0:print("eta>=0"):continue
                    alphas[j]-=labelMat[j]*(Ei-Ej)/eta
                    alphas[j]=clipAlpha(alphas[j],H,L)
                #------------------------------------------    
                #如果改变后的alphaj值变化不大，跳出本次循环    
                if(abs(alphas[j]-alphaJold)<0.00001):print("j not moving\
                enough");continue
                #否则，计算相应的alphai值
                alphas[i]+=labelMat[j]*labelMat[i]*(alphaJold-alphas[j])
                #再分别计算两个alpha情况下对于的b值
                b1=b-Ei-labelMat[i]*(alphas[i]-alphaIold)*\
                    dataMatrix[i,:]*dataMat[i,:].T-\
                    labelMat[j]*(alphas[j]-alphaJold)*\
                    dataMatrix[i,:]*dataMatrix[j,:].T
                b2=b-Ej-labelMat[i]*(alphas[i]-alphaIold)*\
                    dataMatrix[i,:]*dataMatrix[j,:].T-\
                    labelMat[j]*(alphas[j]-alphaJold)*\
                    dataMatrix[j,:]*dataMatrix[j,:].T
                #如果0<alphai<C,那么b=b1
                if(0<alphas[i]) and (C>alphas[i]):b=b1
                #否则如果0<alphai<C,那么b=b1
                elif (0<alphas[j]) and (C>alphas[j]):b=b2
                #否则，alphai，alphaj=0或C
                else:b=(b1+b2)/2.0
                #如果走到此步，表面改变了一对alpha值
                alphaPairsChanged+=1
                print("iter: &d i:%d,paird changed %d",%(iter,i,alphaPairsChanged))
        #最后判断是否有改变的alpha对，没有就进行下一次迭代
        if(alphaPairsChanged==0):iter+=1
        #否则，迭代次数置0，继续循环
        else:iter=0
        print("iteration number: %d" %iter)
    #返回最后的b值和alpha向量
    return b,alphas

#启发式SMO算法的支持函数
#新建一个类的收据结构，保存当前重要的值
class optStruct:
    def __init__(self,dataMatIn,classLabels,C,toler):
        self.X=dataMatIn
        self.labelMat=classLabels
        self.C=C
        self.tol=toler
        self.m=shape(dataMatIn)[0]
        self.alphas=mat(zeros((self.m,1)))
        self.b=0
        self.eCache=mat(zeros((self.m,2)))
#格式化计算误差的函数，方便多次调用
def calcEk(oS,k):
    fXk=float(multiply(oS.alphas,oS.labelMat).T*\
        (oS.X*oS.X[k,:].T))+oS.b
    Ek=fXk-float(oS.labelMat[k])
    return Ek
#修改选择第二个变量alphaj的方法
def selectJ(i,oS,Ei):
    maxK=-1;maxDeltaE=-;Ej=0
    #将误差矩阵每一行第一列置1，以此确定出误差不为0
    #的样本
    oS.eCache[i]=[1,Ei]
    #获取缓存中Ei不为0的样本对应的alpha列表
    validEcacheList=nonzero(oS.Cache[:,0].A)[0]
    #在误差不为0的列表中找出使abs(Ei-Ej)最大的alphaj
    if(len(validEcacheList)>0):
        for k in validEcacheList:
            if k ==i:continue
            Ek=calcEk(oS,k)
            deltaE=abs(Ei-Ek)
            if(deltaE>maxDeltaE):
                maxK=k;maxDeltaE=deltaE;Ej=Ek
        return maxK,Ej
    else:
    #否则，就从样本集中随机选取alphaj
        j=selectJrand(i,oS.m)
        Ej=calcEk(oS,j)
    return j,Ej
#更新误差矩阵
def updateEk(oS,k):
    Ek=calcEk(oS,k)
    oS.eCache[k]=[1,Ek]

#SMO外循环代码
def smoP(dataMatIn,classLabels,C,toler,maxIter,kTup=('lin',0))：
    #保存关键数据
    oS=optStruct(mat(dataMatIn),mat(classLabels).transpose(),C,toler)
    iter=0
    enrireSet=True;alphaPairsChanged=0
    #选取第一个变量alpha的三种情况，从间隔边界上选取或者整个数据集
    while(iter<maxIter)and((alphaPairsChanged>0)or(entireSet)):
        alphaPairsChanged=0
        #没有alpha更新对
        if entireSet:
            for i in range(oS.m):
                alphaPairsChanged+=innerL(i,oS)
            print("fullSet,iter: %d i:%d,pairs changed %d",%\
                (iter,i,alphaPairsChanged))
        else:
            #统计alphas向量中满足0<alpha<C的alpha列表
            nonBoundIs=nonzero((oS.alphas.A)>0)*(oS.alphas.A<C))[0]
            for i in nonBoundIs:
                alphaPairsChanged+=innerL(i,oS)
                print("non-bound,iter: %d i:%d,pairs changed %d",%\
                (iter,i,alphaPairsChanged))
            iter+=1
        if entireSet:entireSet=False
        #如果本次循环没有改变的alpha对，将entireSet置为true，
        #下个循环仍遍历数据集
        elif (alphaPairsChanged==0):entireSet=True
        print("iteration number: %d",%iter)
    return oS.b,oS.alphas

#内循环寻找alphaj
def innerL(i,oS):
    #计算误差
    Ei=calcEk(oS,i)
    #违背kkt条件
    if(((oS.labelMat[i]*Ei<-oS.tol)and(oS.alphas[i]<oS.C))or\    
        ((oS.labelMat[i]*Ei>oS.tol)and(oS.alphas[i]>0))):
        j,Ej=selectJ(i,oS,Ei)
        alphaIold=alphas[i].copy();alphaJold=alphas[j].copy()
        #计算上下界
        if(oS.labelMat[i]!=oS.labelMat[j]):
            L=max(0,oS.alphas[j]-oS.alphas[i])
            H=min(oS.C,oS.C+oS.alphas[j]-oS.alphas[i])
        else:
            L=max(0,oS.alphas[j]+oS.alphas[i]-oS.C)
            H=min(oS.C,oS.alphas[j]+oS.alphas[i])
        if L==H:print("L==H");return 0
        #计算两个alpha值
        eta=2.0*oS.X[i,:]*oS.X[j,:].T-oS.X[i,:]*oS.X[i,:].T-\
            oS.X[j,:]*oS.X[j,:].T
        if eta>=0:print("eta>=0");return 0
        oS.alphas[j]-=oS.labelMat[j]*(Ei-Ej)/eta
        oS.alphas[j]=clipAlpha(oS.alphas[j],H,L)
        updateEk(oS,j)
        if(abs(oS.alphas[j]-alphaJold)<0.00001):
            print("j not moving enough");return 0
        oS.alphas[i]+=oS.labelMat[j]*oS.labelMat[i]*\
            (alphaJold-oS.alphas[j])
        updateEk(oS,i)
        #在这两个alpha值情况下，计算对应的b值
        #注，非线性可分情况，将所有内积项替换为核函数K[i,j]
        b1=oS.b-Ei-oS.labelMat[i]*(oS.alphas[i]-alphaIold)*\
                    oS.X[i,:]*oS.X[i,:].T-\
                    oS.labelMat[j]*(oS.alphas[j]-alphaJold)*\
                    oS.X[i,:]*oS.X[j,:].T
        b2=oS.b-Ej-oS.labelMat[i]*(oS.alphas[i]-alphaIold)*\
                    oS.X[i,:]*oS.X[j,:].T-\
                    oS.labelMat[j]*(oS.alphas[j]-alphaJold)*\
                    oS.X[j,:]*oS.X[j,:].T
        if(0<oS.alphas[i])and (oS.C>oS.alphas[i]):oS.b=b1
        elif(0<oS.alphas[j])and (oS.C>oS.alphas[j]):oS.b=b2
        else:oS.b=(b1+b2)/2.0
        #如果有alpha对更新
        return 1
            #否则返回0
            else return 0

#求出了alpha值和对应的b值，就可以求出对应的w值，以及分类函数值
def predict(alphas,dataArr,classLabels):
    X=mat(dataArr);labelMat=mat(classLabels)
    m,n=shape(X)
    w=zeros((n,1))
    for i in range(m):
        w+=multiply(alphas[i]*labelMat[i],X[i,:].T)
    result=dataArr[0]*mat(ws)+b
    return sign(result)


#径向基核函数是svm常用的核函数
#核转换函数
def kernelTrans(X,A,kTup):
    m,n=shape(X)
    K=mat(zeros((m,1)))
    #如果核函数类型为'lin'
    if kTup[0]=='lin':K=X*A.T
    #如果核函数类型为'rbf':径向基核函数
    #将每个样本向量利用核函数转为高维空间
    elif kTup[0]=='rbf'
        for j in range(m):
            deltaRow=X[j,:]-A
            K[j]=deltaRow*deltaRow.T
        K=exp(K/(-1*kTup[1]**2))
    else：raise NameError('Houston we Have a Problem -- \
    That Kernel is not recognised')
    return K
    
#对核函数处理的样本特征，存入到optStruct中
class optStruct：
    def __init__(self,dataMatIn,classLabels,C,toler,kTup):
        self.X=dataMatIn
        self.labelMat=classLabels
        self.C=C
        self.tol=toler
        self.m=shape(dataMatIn)[0]
        self.alphas=mat(zeros((self.m,1)))
        self.b=0
        self.eCache=mat(zeros((self.m,2)))
        self.K=mat(zeros((self.m,self.m)))
        for i in range(self.m):
            self.K[:,i]=kernelTrans(self.X,self.X[i,:],kTup)


#测试核函数
#用户指定到达率
def testRbf(k1=1.3):
    #第一个测试集
    dataArr,labelArr=loadDataSet('testSetRBF.txt')
    b,alphas=smoP(dataArr,labelArr,200,0.0001,10000,('rbf',k1))
    dataMat=mat(dataArr);labelMat=mat(labelArr).transpose()
    svInd=nonzero(alphas.A>0)[0]
    sVs=dataMat[svInd]
    labelSV=labelMat[svInd]
    print("there are %d Support Vectors",%shape(sVs)[0])
    m,n=shape(dataMat)
    errorCount=0
    for i in range(m):
        kernelEval=kernelTrans(sVs,dataMat[i,:],('rbf',k1))
        predict=kernelEval.T*multiply(labelSV,alphas[svInd])+b
        if sign(predict)!=sign(labelArr[i]):errorCount+=1
    print("the training error rate is: %f",%(float(errorCount)/m))
    #第二个测试集
    dataArr,labelArr=loadDataSet('testSetRBF2.txt')
    dataMat=mat(dataArr);labelMat=mat(labelArr).transpose()
    errorCount=0
    m,n=shape(dataMat)
    for i in range(m):
        kernelEval=kernelTrans(sVs,dataMat[i,:],('rbf',k1))
        predict=kernelEval.T*multiply(labelSV,alphas[svInd])+b
        if sign(predict)!=sign(labelArr[i]):errorCount+=1
    print("the training error rate is: %f",%(float(errorCount)/m))

#实例：手写识别问题
#支持向量机由于只需要保存支持向量，所以相对于KNN保存整个数据集占用更少内存
#且取得可比的效果

#基于svm的手写数字识别
def loadImages(dirName):
    from os import listdir
    hwLabels=[]
    trainingFileList=listdir(dirName)
    m=len(trainingFileList)
    trainingMat=zeros((m,1024))
    for i in range(m):
        fileNameStr=trainingFileList[i]
        fileStr=fileNameStr.split('.')[0]
        classNumStr=int(fileStr.split('_')[0])
        if classNumStr==9:hwLabels.append(-1)
        else:hwLabels.append(1)
        trainingMat[i,:]=img2vector('%s/%s',%(dirName,fileNameStr))
    return hwLabels,trainingMat

#将图像转为向量
def img2vector(fileaddir):
    featVec=zeros((1,1024))
    fr=open(filename)
    for i in range(32):
        lineStr=fr.readline()
        for j in range(32):
            featVec[0,32*i+j]=int(lineStr[j])
    return featVec
    
#利用svm测试数字
def testDigits(kTup=('rbf',10)):
    #训练集
    dataArr,labelArr=loadDataSet('trainingDigits')
    b,alphas=smoP(dataArr,labelArr,200,0.0001,10000,kTup)
    dataMat=mat(dataArr);labelMat=mat(labelArr).transpose()
    svInd=nonzero(alphas.A>0)[0]
    sVs=dataMat[svInd]
    labelSV=labelMat[svInd]
    print("there are %d Support Vectors",%shape(sVs)[0])
    m,n=shape(dataMat)
    errorCount=0
    for i in range(m):
        kernelEval=kernelTrans(sVs,dataMat[i,:],kTup)
        predict=kernelEval.T*multiply(labelSV,alphas[svInd])+b
        if sign(predict)!=sign(labelArr[i]):errorCount+=1
    print("the training error rate is: %f",%(float(errorCount)/m))
    #测试集
    dataArr,labelArr=loadDataSet('testDigits.txt')
    dataMat=mat(dataArr);labelMat=mat(labelArr).transpose()
    errorCount=0
    m,n=shape(dataMat)
    for i in range(m):
        kernelEval=kernelTrans(sVs,dataMat[i,:],('rbf',k1))
        predict=kernelEval.T*multiply(labelSV,alphas[svInd])+b
        if sign(predict)!=sign(labelArr[i]):errorCount+=1
    print("the training error rate is: %f",%(float(errorCount)/m))

