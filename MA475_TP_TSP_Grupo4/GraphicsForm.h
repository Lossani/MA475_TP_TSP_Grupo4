#pragma once

#include "Interface.h"

namespace MA475TPTSPGrupo4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de GraphicsForm
	/// </summary>
	public ref class GraphicsForm : public System::Windows::Forms::Form
	{
	private:
		BufferedGraphics^ buffer;
	private: System::Windows::Forms::Button^ btnAddNode;
	private: System::Windows::Forms::Button^ btnUndoNode;
	private: System::Windows::Forms::Button^ btnCalculateRoute;


		   CInterface^ interfaz;
	public:
		GraphicsForm(void)
		{
			InitializeComponent();
			buffer = BufferedGraphicsManager::Current->Allocate(this->CreateGraphics(), this->ClientRectangle);
			interfaz = gcnew CInterface;
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~GraphicsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnAddNode = (gcnew System::Windows::Forms::Button());
			this->btnUndoNode = (gcnew System::Windows::Forms::Button());
			this->btnCalculateRoute = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &GraphicsForm::timer1_Tick);
			// 
			// btnAddNode
			// 
			this->btnAddNode->Location = System::Drawing::Point(34, 119);
			this->btnAddNode->Name = L"btnAddNode";
			this->btnAddNode->Size = System::Drawing::Size(173, 49);
			this->btnAddNode->TabIndex = 0;
			this->btnAddNode->Text = L"Añadir Nodo";
			this->btnAddNode->UseVisualStyleBackColor = true;
			// 
			// btnUndoNode
			// 
			this->btnUndoNode->Location = System::Drawing::Point(34, 195);
			this->btnUndoNode->Name = L"btnUndoNode";
			this->btnUndoNode->Size = System::Drawing::Size(173, 49);
			this->btnUndoNode->TabIndex = 1;
			this->btnUndoNode->Text = L"Deshacer Nodo";
			this->btnUndoNode->UseVisualStyleBackColor = true;
			// 
			// btnCalculateRoute
			// 
			this->btnCalculateRoute->Location = System::Drawing::Point(34, 264);
			this->btnCalculateRoute->Name = L"btnCalculateRoute";
			this->btnCalculateRoute->Size = System::Drawing::Size(173, 48);
			this->btnCalculateRoute->TabIndex = 2;
			this->btnCalculateRoute->Text = L"Calcular Ruta Optima";
			this->btnCalculateRoute->UseVisualStyleBackColor = true;
			// 
			// GraphicsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(954, 575);
			this->Controls->Add(this->btnCalculateRoute);
			this->Controls->Add(this->btnUndoNode);
			this->Controls->Add(this->btnAddNode);
			this->Name = L"GraphicsForm";
			this->Text = L"GraphicsForm";
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::GraphicsForm_MouseClick);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::GraphicsForm_MouseMove);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::DarkGray);
		interfaz->repetidor();
		interfaz->Graficar(buffer->Graphics);
		buffer->Render();
	}
	private: System::Void GraphicsForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		interfaz->cursor_click(e->X, e->Y);
	}
	private: System::Void GraphicsForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		interfaz->setX(e->X);
		interfaz->setY(e->Y);
	}
	};
}
