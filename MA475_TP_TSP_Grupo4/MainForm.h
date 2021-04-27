#pragma once

#include "TSPSolver.h"
#include <vector>

namespace MA475TPTSPGrupo4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dataGridNodesData;
	private: System::Windows::Forms::Button^ btnAddNode;
	private: System::Windows::Forms::TextBox^ txtNewNodeName;
	private: System::Windows::Forms::Label^ lblNewNodeName;
	private: System::Windows::Forms::Button^ btnResetNodeData;
	private: System::Windows::Forms::Button^ btnSolveBruteForce;
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
			this->dataGridNodesData = (gcnew System::Windows::Forms::DataGridView());
			this->btnAddNode = (gcnew System::Windows::Forms::Button());
			this->txtNewNodeName = (gcnew System::Windows::Forms::TextBox());
			this->lblNewNodeName = (gcnew System::Windows::Forms::Label());
			this->btnResetNodeData = (gcnew System::Windows::Forms::Button());
			this->btnSolveBruteForce = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridNodesData))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridNodesData
			// 
			this->dataGridNodesData->AllowUserToAddRows = false;
			this->dataGridNodesData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridNodesData->Location = System::Drawing::Point(44, 96);
			this->dataGridNodesData->Name = L"dataGridNodesData";
			this->dataGridNodesData->Size = System::Drawing::Size(636, 370);
			this->dataGridNodesData->TabIndex = 0;
			// 
			// btnAddNode
			// 
			this->btnAddNode->Location = System::Drawing::Point(180, 31);
			this->btnAddNode->Name = L"btnAddNode";
			this->btnAddNode->Size = System::Drawing::Size(122, 39);
			this->btnAddNode->TabIndex = 1;
			this->btnAddNode->Text = L"Agregar Nodo";
			this->btnAddNode->UseVisualStyleBackColor = true;
			this->btnAddNode->Click += gcnew System::EventHandler(this, &MainForm::btnAddNode_Click);
			// 
			// txtNewNodeName
			// 
			this->txtNewNodeName->Location = System::Drawing::Point(44, 50);
			this->txtNewNodeName->Name = L"txtNewNodeName";
			this->txtNewNodeName->Size = System::Drawing::Size(113, 20);
			this->txtNewNodeName->TabIndex = 2;
			this->txtNewNodeName->Text = L"Nodo 1";
			// 
			// lblNewNodeName
			// 
			this->lblNewNodeName->AutoSize = true;
			this->lblNewNodeName->Location = System::Drawing::Point(41, 31);
			this->lblNewNodeName->Name = L"lblNewNodeName";
			this->lblNewNodeName->Size = System::Drawing::Size(47, 13);
			this->lblNewNodeName->TabIndex = 3;
			this->lblNewNodeName->Text = L"Nombre:";
			// 
			// btnResetNodeData
			// 
			this->btnResetNodeData->Location = System::Drawing::Point(566, 31);
			this->btnResetNodeData->Name = L"btnResetNodeData";
			this->btnResetNodeData->Size = System::Drawing::Size(114, 33);
			this->btnResetNodeData->TabIndex = 4;
			this->btnResetNodeData->Text = L"Reiniciar";
			this->btnResetNodeData->UseVisualStyleBackColor = true;
			this->btnResetNodeData->Click += gcnew System::EventHandler(this, &MainForm::btnResetNodeData_Click);
			// 
			// btnSolveBruteForce
			// 
			this->btnSolveBruteForce->Location = System::Drawing::Point(545, 472);
			this->btnSolveBruteForce->Name = L"btnSolveBruteForce";
			this->btnSolveBruteForce->Size = System::Drawing::Size(135, 40);
			this->btnSolveBruteForce->TabIndex = 5;
			this->btnSolveBruteForce->Text = L"Resolver";
			this->btnSolveBruteForce->UseVisualStyleBackColor = true;
			this->btnSolveBruteForce->Click += gcnew System::EventHandler(this, &MainForm::btnSolveBruteForce_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(744, 521);
			this->Controls->Add(this->btnSolveBruteForce);
			this->Controls->Add(this->btnResetNodeData);
			this->Controls->Add(this->lblNewNodeName);
			this->Controls->Add(this->txtNewNodeName);
			this->Controls->Add(this->btnAddNode);
			this->Controls->Add(this->dataGridNodesData);
			this->Name = L"MainForm";
			this->Text = L"MA475 - TSP Solver - Grupo 4";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridNodesData))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		dataGridNodesData->RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
	}

	private: System::Void btnAddNode_Click(System::Object^ sender, System::EventArgs^ e) {

		int nodeCount = dataGridNodesData->Columns->Count;
		int newNode = nodeCount + 1;

		String^ nodeName = txtNewNodeName->Text != "" ? txtNewNodeName->Text : "Nodo " + newNode;

		dataGridNodesData->Columns->Add(nodeName, nodeName);
		dataGridNodesData->Rows->Add();
		dataGridNodesData->Rows[nodeCount]->HeaderCell->Value = nodeName;
		dataGridNodesData[nodeCount, nodeCount]->ReadOnly = true;
		dataGridNodesData[nodeCount, nodeCount]->Value = "0";

		txtNewNodeName->Text = "Nodo " + (newNode + 1);
	}
	private: System::Void btnResetNodeData_Click(System::Object^ sender, System::EventArgs^ e) {
		dataGridNodesData->Rows->Clear();
		dataGridNodesData->Columns->Clear();
		dataGridNodesData->Refresh();
	}
private: System::Void btnSolveBruteForce_Click(System::Object^ sender, System::EventArgs^ e) {

	switch (dataGridNodesData->Columns->Count)
	{
	case 0:
		MessageBox::Show("No ha ingresado datos de los nodos.");
		break;
	case 1:
	case 2:
		MessageBox::Show("Calculo obvio");
		break;
	default:
		vector<vector<int>> nodeData;

		for (int i = 0; i < dataGridNodesData->Rows->Count; ++i)
		{
			vector<int> rowData;
			for (int j = 0; j < dataGridNodesData->Columns->Count; ++j)
			{
				rowData.push_back(Convert::ToInt32(dataGridNodesData[i, j]->Value));
			}

			nodeData.push_back(rowData);
		}

		TSPSolver* solver = new TSPSolver(nodeData);

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

		break;
	}
}
};
}
