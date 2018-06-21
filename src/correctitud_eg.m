% dirList = glob("peter_in/*_At*");
dirList = glob("peter_in/*");

for i = 1:2:length(dirList)
   dirname = dirList{i,1};
   
   A = csvread(dirname);
   A_t = A';
   AtA = A_t * A;
   
   dirname = dirList{i+1,1};
   
   b = csvread(dirname);
   
   Atb = A_t * b;
   
   x = AtA\Atb; % resolví ecus lineales
   
   a = num2str(ceil(i/2));
   xout_file = ["peter_out/" a "_octave.csv"];
   csvwrite(xout_file, x);   
end