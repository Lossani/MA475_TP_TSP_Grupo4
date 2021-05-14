#pragma once

#include "Interface.h"
#include "MainForm.h"
#include <functional>

#define T_NODE vector<vector<int>>

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
	private: System::Windows::Forms::Button^ btnAddNode;
	private: System::Windows::Forms::Button^ btnUndoNode;
	private: System::Windows::Forms::PictureBox^ pBGraphicNodes;



		   Interface^ interface;
		   BufferedGraphics^ buffer;
		   Form^ parent;
	public:
		GraphicsForm(Interface^ interface_instance, Form^ parent_form) : interface(interface_instance), parent(parent_form)
		{
			InitializeComponent();
			pBGraphicNodes->SetBounds(0, 80, this->Bounds.Right, this->Bounds.Bottom - 80);
			buffer = BufferedGraphicsManager::Current->Allocate(pBGraphicNodes->CreateGraphics(), pBGraphicNodes->ClientRectangle);
			//interface = gcnew Interface;
			//
			//TODO: agregar código de constructor aquí
			//
		}

		GraphicsForm(void)
		{
			InitializeComponent();
			pBGraphicNodes->SetBounds(0, 80, this->Bounds.Right, this->Bounds.Bottom - 80);
			buffer = BufferedGraphicsManager::Current->Allocate(pBGraphicNodes->CreateGraphics(), pBGraphicNodes->ClientRectangle);
			interface = gcnew Interface;
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
	private: System::Windows::Forms::Timer^ drawingTimer;
	protected:

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
			this->drawingTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnAddNode = (gcnew System::Windows::Forms::Button());
			this->btnUndoNode = (gcnew System::Windows::Forms::Button());
			this->pBGraphicNodes = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBGraphicNodes))->BeginInit();
			this->SuspendLayout();
			// 
			// drawingTimer
			// 
			this->drawingTimer->Enabled = true;
			this->drawingTimer->Interval = 30;
			this->drawingTimer->Tick += gcnew System::EventHandler(this, &GraphicsForm::drawingTimer_Tick);
			// 
			// btnAddNode
			// 
			this->btnAddNode->AutoSize = true;
			this->btnAddNode->Location = System::Drawing::Point(12, 12);
			this->btnAddNode->Name = L"btnAddNode";
			this->btnAddNode->Size = System::Drawing::Size(173, 49);
			this->btnAddNode->TabIndex = 0;
			this->btnAddNode->Text = L"Añadir Nodo";
			this->btnAddNode->UseVisualStyleBackColor = true;
			this->btnAddNode->Click += gcnew System::EventHandler(this, &GraphicsForm::btnAddNode_Click);
			// 
			// btnUndoNode
			// 
			this->btnUndoNode->AutoSize = true;
			this->btnUndoNode->Location = System::Drawing::Point(191, 12);
			this->btnUndoNode->Name = L"btnUndoNode";
			this->btnUndoNode->Size = System::Drawing::Size(173, 49);
			this->btnUndoNode->TabIndex = 1;
			this->btnUndoNode->Text = L"Deshacer Nodo";
			this->btnUndoNode->UseVisualStyleBackColor = true;
			this->btnUndoNode->Click += gcnew System::EventHandler(this, &GraphicsForm::btnUndoNode_Click);
			// 
			// pBGraphicNodes
			// 
			this->pBGraphicNodes->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->pBGraphicNodes->Location = System::Drawing::Point(12, 78);
			this->pBGraphicNodes->Name = L"pBGraphicNodes";
			this->pBGraphicNodes->Size = System::Drawing::Size(930, 485);
			this->pBGraphicNodes->TabIndex = 3;
			this->pBGraphicNodes->TabStop = false;
			this->pBGraphicNodes->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::pBGraphicNodes_MouseClick);
			this->pBGraphicNodes->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::pBGraphicNodes_MouseMove);
			// 
			// GraphicsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(954, 575);
			this->Controls->Add(this->pBGraphicNodes);
			this->Controls->Add(this->btnUndoNode);
			this->Controls->Add(this->btnAddNode);
			this->Name = L"GraphicsForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"GraphicsForm";
			this->Load += gcnew System::EventHandler(this, &GraphicsForm::GraphicsForm_Load);
			this->ResizeEnd += gcnew System::EventHandler(this, &GraphicsForm::GraphicsForm_ResizeEnd);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::GraphicsForm_MouseClick);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &GraphicsForm::GraphicsForm_MouseMove);
			this->Resize += gcnew System::EventHandler(this, &GraphicsForm::GraphicsForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pBGraphicNodes))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:

			void update_node_table();

	private: System::Void drawingTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::DarkGray);
		interface->draw(buffer->Graphics);
		buffer->Render();
	}
	private: System::Void GraphicsForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		
	}
	private: System::Void GraphicsForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

	}
	private: System::Void btnAddNode_Click(System::Object^ sender, System::EventArgs^ e) {
		interface->new_node();
	}
private: System::Void btnUndoNode_Click(System::Object^ sender, System::EventArgs^ e) {
	interface->delete_last_node();
	update_node_table();
}
private: System::Void pBGraphicNodes_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	interface->drawer_iterator(buffer->Graphics, e->X, e->Y, false);
}
private: System::Void pBGraphicNodes_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	interface->drawer_iterator(buffer->Graphics, e->X, e->Y, true);
	update_node_table();
}
private: System::Void GraphicsForm_Resize(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void GraphicsForm_ResizeEnd(System::Object^ sender, System::EventArgs^ e) {
	pBGraphicNodes->SetBounds(0, 80, this->Bounds.Right, this->Bounds.Bottom - 80);

	buffer = BufferedGraphicsManager::Current->Allocate(pBGraphicNodes->CreateGraphics(), pBGraphicNodes->ClientRectangle);
}
private: System::Void GraphicsForm_Load(System::Object^ sender, System::EventArgs^ e) {
	this->ControlBox = false;
}
};
}
