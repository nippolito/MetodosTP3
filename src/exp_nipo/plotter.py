# -*- coding: utf-8 -*-

import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import random
import math
import numpy as np

def expECMOpuestosTomo():
	df1 = pd.read_csv('opuestosTomo1_capFinal.csv')

	# Dens2 = df1[df1['densidad'] == 0.2]
	# Dens5 = df1[df1['densidad'] == 0.5]

	xdata  = df1['pctjeRayos']

	ydata = df1['ECM']

	plt.plot(xdata, ydata, "r.", alpha = 0.5, label='ECM segun %rayos')

	plt.xlabel('%rayos con respecto a #pixeles')
	plt.ylabel('ECM')
	plt.title('Generador de rayos opuestos')

	plt.legend()
	plt.show()

def expECMCruzadosTomo():
	df1 = pd.read_csv('cruzadosTomo1_capFinal.csv')

	# Dens2 = df1[df1['densidad'] == 0.2]
	# Dens5 = df1[df1['densidad'] == 0.5]

	xdata  = df1['pctjeRayos']

	ydata = df1['ECM']

	plt.plot(xdata, ydata, "b.", alpha = 0.5, label='ECM segun %rayos')

	plt.xlabel('%rayos con respecto a #pixeles')
	plt.ylabel('ECM')
	plt.title('Generador de rayos cruzados')

	plt.legend()
	plt.show()

def expECMFijosTomo():
	df1 = pd.read_csv('fijosTomo1_capFinal.csv')

	# Dens2 = df1[df1['densidad'] == 0.2]
	# Dens5 = df1[df1['densidad'] == 0.5]

	xdata  = df1['pctjeRayos']

	ydata = df1['ECM']

	plt.plot(xdata, ydata, "g.", alpha = 0.5, label='ECM segun %rayos')

	plt.xlabel('%rayos con respecto a #pixeles')
	plt.ylabel('ECM')
	plt.title('Generador de rayos fijos')

	plt.legend()
	plt.show()

def expECMAleatoriosTomo():
	df1 = pd.read_csv('aleatoriosTomo1_capFinal.csv')

	# Dens2 = df1[df1['densidad'] == 0.2]
	# Dens5 = df1[df1['densidad'] == 0.5]

	xdata  = df1['pctjeRayos']

	ydata = df1['ECM']

	plt.plot(xdata, ydata, "y.", alpha = 0.5, label='ECM segun %rayos')

	plt.xlabel('%rayos con respecto a #pixeles')
	plt.ylabel('ECM')
	plt.title('Generador de rayos aleatorios')

	plt.legend()
	plt.show()


def expTiemposGeneradoresTomo():
	df1 = pd.read_csv('opuestosTomo1_capFinal.csv')
	df2 = pd.read_csv('cruzadosTomo1_capFinal.csv')
	df3 = pd.read_csv('fijosTomo1_capFinal.csv')
	df4 = pd.read_csv('aleatoriosTomo1_capFinal.csv')

	# Dens2 = df1[df1['densidad'] == 0.2]
	# Dens5 = df1[df1['densidad'] == 0.5]

	xdata  = df1['pctjeRayos']

	ydata1 = df1['tiempo']
	ydata2 = df2['tiempo']
	ydata3 = df3['tiempo']
	ydata4 = df4['tiempo']

	plt.plot(xdata, ydata1, "r.", alpha = 0.5, label='Rayos Opuestos')
	plt.plot(xdata, ydata2, "b.", alpha = 0.5, label='Rayos Cruzados')
	plt.plot(xdata, ydata3, "g.", alpha = 0.5, label='Rayos Punto Fijo')
	plt.plot(xdata, ydata4, "y.", alpha = 0.5, label='Rayos Aleatorios')

	plt.xlabel('%rayos con respecto a #pixeles')
	plt.ylabel('tiempo')
	plt.title('Generadores - tiempo algoritmo en ms')

	plt.legend()
	plt.show()

# expECMOpuestosTomo()
# expECMCruzadosTomo()
expECMFijosTomo()
# expECMAleatoriosTomo()
# expTiemposGeneradoresTomo()