#include "MainForm.h"
using namespace MA475TPTSPGrupo4;
using namespace System;

[STAThread]

void main()
{
	Windows::Forms::Application::EnableVisualStyles();
	Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	Windows::Forms::Application::Run(gcnew MainForm());
}

MA475TPTSPGrupo4::MainForm::MainForm(void)
{
	solver = new TSPSolver();
	main_interface = gcnew Interface(solver);
	graphicsForm = gcnew GraphicsForm(main_interface, this);
	InitializeComponent();
	//
	//TODO: agregar código de constructor aquí
	//
}
