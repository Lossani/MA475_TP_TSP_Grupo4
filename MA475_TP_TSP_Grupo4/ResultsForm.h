#pragma once

namespace MA475TPTSPGrupo4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de ResultsForm
	/// </summary>
	public ref class ResultsForm : public System::Windows::Forms::Form
	{
	public:
		ResultsForm(String^ results)
		{
			InitializeComponent();
			txtResults->Text = results;
		}

		ResultsForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~ResultsForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ txtResults;
	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtResults = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// txtResults
			// 
			this->txtResults->Location = System::Drawing::Point(12, 12);
			this->txtResults->Multiline = true;
			this->txtResults->Name = L"txtResults";
			this->txtResults->ReadOnly = true;
			this->txtResults->Size = System::Drawing::Size(743, 412);
			this->txtResults->TabIndex = 0;
			// 
			// ResultsForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(767, 436);
			this->Controls->Add(this->txtResults);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MaximizeBox = false;
			this->Name = L"ResultsForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Resultados";
			this->Load += gcnew System::EventHandler(this, &ResultsForm::ResultsForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ResultsForm_Load(System::Object^ sender, System::EventArgs^ e) {
		txtResults->Select(0, 0);
	}
	};
}
