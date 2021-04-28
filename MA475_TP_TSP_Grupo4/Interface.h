#pragma once

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <iostream>
#include <functional>
#include <vector>
#include <math.h>
#include "TSPSolver.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace std;

#define radio 10

class CAlineacion
{
public:
	CAlineacion(int x, int y, int X, int Y) {
		this->x = x;
		this->y = y;
		this->Y = Y;
		this->X = X;
		dibujado = true;
		//distancia_cuadrada = 0;
	}
	~CAlineacion() {}
	void Graficar(Graphics^ buff) {
		buff->DrawLine(gcnew Pen(Color::Aqua), x, y, X, Y);
	}
	bool existe_dibujo() {
		return dibujado;
	}
	double distancia() {
		int entre = 10;
		int a = abs(X / entre - x / entre);
		int b = abs(Y / entre - y / entre);
		int c = sqrt((pow(a, 2)) + (pow(b, 2)));
		return c;
	}
	int getmedioX() {
		if (X > x)
			return x + abs(X - x) / 2;
		else
			return X + abs(X - x) / 2;
	}
	int getmedioY() {
		if (Y > y)
			return y + abs(Y - y) / 2;
		else
			return Y + abs(Y - y) / 2;
	}
	void setX(int X) {
		x = X;
	}
	void setY(int Y) {
		y = Y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
private:
	bool dibujado;
	int x, y, X, Y;
};

class CFlecha
{
public:
	CFlecha(int x, int y, bool i) {
		this->x = x;
		this->y = y;
		this->i = i;
	}
	~CFlecha() {}
	void Graficar(Graphics^ buff) {
		if (i)
			buff->DrawString("Inicio", gcnew System::Drawing::Font(L"Gill Sans MT", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::DarkSeaGreen, Rectangle(x - 16, y - 40, 2000, 2000));
		else
			buff->DrawString("Final", gcnew System::Drawing::Font(L"Gill Sans MT", 10.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::DarkSeaGreen, Rectangle(x - 16, y - 40, 2000, 2000));
		buff->FillRectangle(gcnew SolidBrush(Color::DarkSeaGreen), x - 2, y - 20, 4, 15);
		for (int i = 4; i < 12; i++) {
			buff->DrawLine(gcnew Pen(Color::DarkSeaGreen), x - 10, y - i, x, y);
			buff->DrawLine(gcnew Pen(Color::DarkSeaGreen), x + 10, y - i, x, y);
		}

	}
private:
	int x, y;
	bool i;
};

class CCirculos
{
public:
	CCirculos(int x, int y) {
		this->x = x;
		this->y = y;
		seguir = true;
	}
	~CCirculos() {
	}
	void Graficar(Graphics^ buff) {

		//buff->DrawLine(lapicero, Point(75, 125), Point(375, 325));
		buff->FillEllipse(gcnew SolidBrush(Color::DarkOrange), System::Drawing::Rectangle(x - radio / 2, y - radio / 2, radio, radio));
	}
	void seguir_on() {
		seguir = true;
	}
	void seguir_off() {
		seguir = false;
	}
	bool seguro_seguir() {
		return seguir;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int X) {
		x = X;
	}
	void setY(int Y) {
		y = Y;
	}
private:
	bool seguir;
	int x, y;

};
ref class CInterface
{
private:
	vector<vector<int>>* nodeTable;
public:
	CInterface() {
		circulo = new vector<CCirculos*>;
		linea = new vector<CAlineacion*>;
		texto = gcnew String(" ");

		Zona = Rectangle(170, 80, 600, 500);
		titulo = Rectangle(0, 0, 750, 80);
		x = 0; y = 0;
		R = 100, G = 50, B = 50;
		dR = 2, dG = 2, dB = 2;

		click = false;
	}
	~CInterface() {
		for (int i = 0; i < circulo->size(); ++i) {
			delete circulo->at(i);
		}delete circulo;
		for (int i = 0; i < linea->size(); ++i) {
			delete linea->at(i);
		}delete linea;

	}
	void Graficar(Graphics^ buff) {

		buff->FillRectangle(gcnew SolidBrush(Color::White), Zona);
		{
			if (R > 155)
				dR = -2;
			else if (R < 3)
				dR = 2;
			if (G > 155)
				dG = -4;
			else if (G < 5)
				dG = 4;
			if (B > 155)
				dB = -1;
			else if (B < 2)
				dB = 1;
			R = dR + R;
			G = dG + G;
			B = dB + B;
		}
		buff->FillRectangle(gcnew SolidBrush(Color::FromArgb(R, G, B)), titulo);

		for (int i = 0; i < linea->size(); ++i) {
			linea->at(i)->Graficar(buff);
			buff->DrawString(linea->at(i)->distancia().ToString() + " Km", gcnew System::Drawing::Font(L"Gill Sans MT", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::Chocolate, Rectangle(linea->at(i)->getmedioX(), linea->at(i)->getmedioY(), 2000, 2000));
		}
		for (int i = 0; i < circulo->size(); ++i) {
			circulo->at(i)->Graficar(buff);
			//if(i!=1 && i!= circulo->size()-1)
			buff->DrawString((i + 1).ToString(), gcnew System::Drawing::Font(L"Gill Sans MT", 8.0F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::Black, Rectangle(circulo->at(i)->getX() - 5, circulo->at(i)->getY() - 18, 1000, 1000));
		}
		if (circulo->size() > 0) {
			flecha_inicio = new CFlecha(circulo->at(0)->getX(), circulo->at(0)->getY() - 20, 1);
			flecha_inicio->Graficar(buff);
			delete flecha_inicio;
		}
		if (circulo->size() > 1) {
			flecha_final = new CFlecha(circulo->at(circulo->size() - 1)->getX(), circulo->at(circulo->size() - 1)->getY() - 20, 0);
			flecha_final->Graficar(buff);
			delete flecha_final;
		}
		{//texto menu
			buff->DrawString("Problema del Viajero", gcnew System::Drawing::Font(L"Gill Sans MT", 15.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::White, Rectangle(20, 10, 1000, 200));
			buff->DrawString("Lugares: " + circulo->size().ToString() + " Rutas: " + linea->size().ToString(), gcnew System::Drawing::Font(L"Gill Sans MT", 15.0F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)), Brushes::White, Rectangle(200, 45, 1000, 200));
		}
	}
	void cursor_click(int x, int y) {
		if (Zona.IntersectsWith(Rectangle(x, y, 0, 0))) { // reset lineas
			while (linea->size() != 0) {
				linea->erase(linea->begin());
			}
		}
		if (Rectangle(0, 100, 150, 35).IntersectsWith(Rectangle(x, y, 0, 0))) //boton 1 con mouse
			nuevo_circulo(Zona.X, Zona.Y);
		else if (Rectangle(0, 160, 150, 35).IntersectsWith(Rectangle(x, y, 0, 0))) { //boton 2 con mouse	
			while (linea->size() != 0) {
				linea->erase(linea->begin() + linea->size() - 1);
			}
			circulo->erase(circulo->begin() + circulo->size() - 1);
			unir_circulos();
		}
		else if (Rectangle(0, 220, 150, 35).IntersectsWith(Rectangle(x, y, 0, 0))) //boton 1 con mouse
		{
			TSPSolver* solver = new TSPSolver(*nodeTable);

			solver->solveBruteForce();

			vector<int> resultRoute = solver->getOptimalRouteResult();
			int resultCost = solver->getRouteCostResult();

			MessageBox::Show("Costo de la ruta optima: " + resultCost);

			String^ result = "";

			for (int node : resultRoute)
			{
				result += node + " -> ";
			}

			result += "0";

			MessageBox::Show(result);
		}
		else if (Zona.IntersectsWith(Rectangle(x, y, 0, 0))) { // click en zona blanca
			for (int i = 0; i < circulo->size(); ++i) {
				circulo->at(i)->seguir_off();
			}
			//if (circulo->size() >linea->size())
			unir_circulos();
		}
	}
	void nuevo_circulo(int x, int y) {
		CCirculos* circu = new CCirculos(x, y);
		if (circu) {
			circulo->push_back(circu);
		}
	}
	CAlineacion* nueva_linea(int x, int y, int X, int Y) {
		CAlineacion* lin = new CAlineacion(x, y, X, Y);
		if (lin) {
			linea->push_back(lin);
		}
		return lin;
	}

	void unir_circulos() {
		vector<int> row(circulo->size());
		vector<vector<int>> table(circulo->size());

		for (int i = 0; i < circulo->size(); ++i)
		{
			table[i] = row;
		}

		for (int i = 0; i < circulo->size(); ++i) {
			if (i > 0) {
				for (int j = 0; j < i; j++)
				{
					table[j][i] = nueva_linea(circulo->at(i)->getX(), circulo->at(i)->getY(), circulo->at(j)->getX(), circulo->at(j)->getY())->distancia();// linea de circulo a circulo anterior
					table[i][j] = table[j][i];
				}
			}
		}

		nodeTable = new vector<vector<int>>(table);

		//String^ text = "";
		//for (int i = 0; i < table.size(); ++i)
		//{
		//	for (int j = 0; j < table[i].size(); ++j)
		//	{
		//		text += table[i][j] + " ";
		//	}

		//	text += "\n";
		//}

		//MessageBox::Show(text);

	}

	void repetidor() {
		for (int i = 0; i < circulo->size(); ++i) {
			if (circulo->at(i)->seguro_seguir() && (Zona.IntersectsWith(Rectangle(x, y, 0, 0)))) {
				circulo->at(i)->setX(x);
				circulo->at(i)->setY(y);
			}
		}
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	void setX(int X) {
		x = X;
	}
	void setY(int Y) {
		y = Y;
	}
private:
	bool click;
	int x, y;
	int R, G, B;
	int dR, dG, dB;
	vector<CCirculos*>* circulo;
	vector<CAlineacion*>* linea;

	Rectangle Zona;
	Rectangle titulo;
	CFlecha* flecha_inicio;
	CFlecha* flecha_final;
	String^ texto;
};

#endif