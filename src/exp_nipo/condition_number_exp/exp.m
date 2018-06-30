dirList = glob("in_matrix/in/*_At*");

condnum_normal = eye(length(dirList) / 2, 1);
condnum_modif = eye(length(dirList) / 2, 1);

for i = 1:2:length(dirList)
   disp("Iter")
   dirname = dirList{i,1};
   
   AtA = csvread(dirname);
   
   condnum_normal([ceil(i/2)]) = cond(AtA,2);
   
   dirname = dirList{i+1,1};
   
   Atb = csvread(dirname);
   
   x1 = AtA\Atb; % esto en realidad es (AtA)^-1 * Atb
   % solo que en octave se computa sin resolver la inversa
   % y es lo que se utiliza para resolver sist de ecus lineales
   
   % hasta acá en x resolví ecus normales y llené el vector de números de condición
   % ahora quiero guardar x en un csv
   
   a1 = num2str(ceil(i/2));
   outfile_normal = ["out_images/" a1 "_normal.csv"];
   csvwrite(outfile_normal, x1);
   
   % ahora quiero hacer exactamente lo mismo
   % pero con el método para bajar número de condición
   
   [DD, AtA_modif] = balance(AtA);
   
   condnum_modif([ceil(i/2)]) = cond(AtA_modif, 2);
   
   x2 = AtA_modif \ Atb;
   
   outfile_modif = ["out_images/" a1 "_modif.csv"];
   csvwrite(outfile_modif, x2);
   
   
end

csvwrite("out_images/32x32/cond_numbers_normal.csv", condnum_normal);
csvwrite("out_images/32x32/cond_numbers_modif.csv", condnum_modif);