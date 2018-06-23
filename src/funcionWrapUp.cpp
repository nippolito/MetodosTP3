//PARAMETROS: un vector de rayos, donde cada rayo esta dado por dos puntos. y pRuido parametro del ruido a generar
	//PRECONDICION:
		//-La instancia de TCSimulator debe estar limpia. Esto es, no puede haber nada en "rayos" ni "tiempos"
	vector<double> obtenerImagenPorRayos(vector<pair<pair<double,double>, pair<double,double> > > coordenadasRayos, double pRuido, int ordenDeMagnitud){

		//Idea:
		//1 - Se guarda la imagen original para poder compararla/restaurarla al final. Luego, se agrega ruido. 
		//2 - Se generan los rayos a partir de los puntos con la funcion de grego.
		//3 - Por cada rayo, se busca en la imagen el tiempo total en la imagen fuente.
		//4 - Se guarda el rayo (que es una matriz rala) como fila en una nueva matriz A y el tiempo de cada rayo Ti en un vector B
		//5 - Habiendo hecho eso para cada rayo, se discretiza y se resuelve el sistema de ecuaciones.
		//6 - Se devuelve el vector resultado y se regenera la imagen (se escupe en file sistem)
		//7 - Finalmente se restaura la imagen original

		int cantRayos = coordenadasRayos.size();
		
		
		//1
		//La funcion que toma el tiempo de recorrido, lo hace sobre la imagen guardada en esta instancia de TCSimulator.
		Image* imagenOriginal = new Image();
		imagenOriginal->imageBuffer = imageMatrix->imageBuffer;

		Image* imagenConRuido = new Image();			
		
		//TIPO DE RUIDO HARDCODEADO. Si se quiere usar otro modificar la linea
		addSnPNoiseToSimulation(imagenConRuido, pRuido);
		cout << "ya agrego ruido" << endl;

		//reemplazo la imagen original por la imagen con ruido
		imageMatrix->imageBuffer = imagenConRuido->imageBuffer;

		//4
		generarRayos(cantRayos, coordenadasRayos);

		cout << "Rayos y tiempos creados" << endl;

		//5 y 6
		Image* resImagen = regenerarImagenConDiscretizacion(ordenDeMagnitud);

		//"solucion" es otro atributo de TCSimulator para guardar la solucion. 
		vector<double> resVector = solucion;
		cout << "sistema resuelto. falta crear imagen" << endl;

		resImagen->SaveImage("../imgRes/resultadoRayos.ppm", PPM_LOADER_PIXEL_TYPE_RGB_8B);

		//7
		imageMatrix->imageBuffer = imagenOriginal->imageBuffer;

		return resVector;

	}


