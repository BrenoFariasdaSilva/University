function [x] = geneticAlg()


% load trainingMM2.mat;
% load testingMM2.mat ;
% 
% labelTest = testingMM(:,end);
% matTreino = trainingMM(:,1:132);
% matTeste =  testingMM(:,1:132);
% 
% global labelTest
% global matTreino 
% global matTeste


options = optimoptions('ga','PlotFcn', {@gaplotbestf, @gaplotbestindiv}, 'PopulationType', 'bitstring', 'MaxGenerations',200 );
[x] = ga(@ag_kNN,132,options) 


end