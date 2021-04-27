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
