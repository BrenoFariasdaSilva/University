function [rate] = oneFeature()

load trainingMM2.mat;
load testingMM2.mat ;

labelTest = testingMM(:,end);
matTreino = trainingMM(:,1:132);
matTeste =  testingMM(:,1:132);

x = zeros(1,132) ;

%  FEATURE QUE DESEJA ESCOLHER (1 A 132)
feat = 99 ;

x(1,feat) = 1; 

soma = sum(x)

t = length (x);

ci = 1 ;
for i = 1 : t
    if (x(i) == 1)
        matN(:,ci) = matTreino(:,i);
        matT2(:,ci) = matTeste(:,i);
        ci = ci + 1 ;
    end
end
%k-NN classifier
Mdl = fitcknn(matN,labelTest,'NumNeighbors',3,'Standardize',1) ;
[label,score,cost] = predict(Mdl,matT2) ;
[C,order] = confusionmat(label,labelTest) ;
fitness = sum(diag(C)) / 1000 ;

rate = fitness ;

end