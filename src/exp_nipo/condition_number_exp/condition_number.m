% creo cell structure, lo que está adentro del glob
% es la carpeta y los nombres de los archivos que son matrices en csv

dirList = glob("carlos/carlos*");

% loopeo por los elementos de cell

out = eye(length(dirList), 1);

for i = 1:length(dirList)
   dirname = dirList{i,1};  % me quedo con un item
   
   x = csvread(dirname);
   
   out([i, 1]) = cond(x,2);
   
end

% luego de este loop el vector columna 'out'
% tiene todos los números de condición en cada uno de sus elementos
% siempre cuando hablo de número de condición tomo norma 2

csvwrite("cond_numbers.csv", out);

% ahora pasé los números de condición al archivo csv