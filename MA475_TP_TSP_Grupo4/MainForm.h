#pragma once

#include "TSPSolver.h"
#include "GraphicsForm.h"
#include "ResultsForm.h"
#include <vector>
#include <thread>
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
	/// Resumen de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		TSPSolver* solver;
		Interface^ main_interface;
		Form^ graphicsForm;
		Form^ resultsForm;
	private: System::Windows::Forms::TextBox^ txtMaxComputingTime;

	private: System::Windows::Forms::CheckBox^ cBLimitComputingTime;

	private: System::Windows::Forms::Button^ btnSolve;
	private: System::Windows::Forms::ComboBox^ comboBoxSolveMethod;
	private: System::Windows::Forms::Label^ lblSolveMethod;
	private: System::Windows::Forms::Button^ btnDeleteNode;
	private: System::Windows::Forms::ComboBox^ comboBoxDeleteNode;
	private: System::Windows::Forms::Label^ lblDeleteNodeSelection;
	private: System::Windows::Forms::ComboBox^ comboBoxInitNode;
	private: System::Windows::Forms::Label^ lblInitPoint;

	public:
		

		MainForm(void);

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


	private: System::Windows::Forms::CheckBox^ cBShowGraphicsForm;
	private: System::Windows::Forms::GroupBox^ groupGeneralOptions;
	private: System::Windows::Forms::GroupBox^ groupOperationOptions;
	private: System::Windows::Forms::Label^ lblNodeTable;
	private: System::Windows::Forms::NumericUpDown^ numThreadsToUse;

	private: System::Windows::Forms::CheckBox^ cBUseMultithreading;

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
			this->cBShowGraphicsForm = (gcnew System::Windows::Forms::CheckBox());
			this->groupGeneralOptions = (gcnew System::Windows::Forms::GroupBox());
			this->txtMaxComputingTime = (gcnew System::Windows::Forms::TextBox());
			this->cBLimitComputingTime = (gcnew System::Windows::Forms::CheckBox());
			this->numThreadsToUse = (gcnew System::Windows::Forms::NumericUpDown());
			this->cBUseMultithreading = (gcnew System::Windows::Forms::CheckBox());
			this->groupOperationOptions = (gcnew System::Windows::Forms::GroupBox());
			this->btnSolve = (gcnew System::Windows::Forms::Button());
			this->comboBoxSolveMethod = (gcnew System::Windows::Forms::ComboBox());
			this->lblSolveMethod = (gcnew System::Windows::Forms::Label());
			this->btnDeleteNode = (gcnew System::Windows::Forms::Button());
			this->comboBoxDeleteNode = (gcnew System::Windows::Forms::ComboBox());
			this->lblDeleteNodeSelection = (gcnew System::Windows::Forms::Label());
			this->comboBoxInitNode = (gcnew System::Windows::Forms::ComboBox());
			this->lblInitPoint = (gcnew System::Windows::Forms::Label());
			this->lblNodeTable = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridNodesData))->BeginInit();
			this->groupGeneralOptions->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numThreadsToUse))->BeginInit();
			this->groupOperationOptions->SuspendLayout();
			this->SuspendLayout();
			// 
			// dataGridNodesData
			// 
			this->dataGridNodesData->AllowUserToAddRows = false;
			this->dataGridNodesData->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridNodesData->Location = System::Drawing::Point(284, 28);
			this->dataGridNodesData->Name = L"dataGridNodesData";
			this->dataGridNodesData->Size = System::Drawing::Size(1031, 599);
			this->dataGridNodesData->TabIndex = 0;
			// 
			// btnAddNode
			// 
			this->btnAddNode->Location = System::Drawing::Point(168, 19);
			this->btnAddNode->Name = L"btnAddNode";
			this->btnAddNode->Size = System::Drawing::Size(92, 39);
			this->btnAddNode->TabIndex = 1;
			this->btnAddNode->Text = L"Agregar";
			this->btnAddNode->UseVisualStyleBackColor = true;
			this->btnAddNode->Click += gcnew System::EventHandler(this, &MainForm::btnAddNode_Click);
			// 
			// txtNewNodeName
			// 
			this->txtNewNodeName->Location = System::Drawing::Point(12, 38);
			this->txtNewNodeName->Name = L"txtNewNodeName";
			this->txtNewNodeName->Size = System::Drawing::Size(83, 20);
			this->txtNewNodeName->TabIndex = 2;
			this->txtNewNodeName->Text = L"Nodo 1";
			// 
			// lblNewNodeName
			// 
			this->lblNewNodeName->AutoSize = true;
			this->lblNewNodeName->Location = System::Drawing::Point(9, 19);
			this->lblNewNodeName->Name = L"lblNewNodeName";
			this->lblNewNodeName->Size = System::Drawing::Size(74, 13);
			this->lblNewNodeName->TabIndex = 3;
			this->lblNewNodeName->Text = L"Agregar nodo:";
			// 
			// btnResetNodeData
			// 
			this->btnResetNodeData->Location = System::Drawing::Point(145, 132);
			this->btnResetNodeData->Name = L"btnResetNodeData";
			this->btnResetNodeData->Size = System::Drawing::Size(114, 33);
			this->btnResetNodeData->TabIndex = 4;
			this->btnResetNodeData->Text = L"Reiniciar";
			this->btnResetNodeData->UseVisualStyleBackColor = true;
			this->btnResetNodeData->Click += gcnew System::EventHandler(this, &MainForm::btnResetNodeData_Click);
			// 
			// cBShowGraphicsForm
			// 
			this->cBShowGraphicsForm->AutoSize = true;
			this->cBShowGraphicsForm->Location = System::Drawing::Point(6, 19);
			this->cBShowGraphicsForm->Name = L"cBShowGraphicsForm";
			this->cBShowGraphicsForm->Size = System::Drawing::Size(138, 17);
			this->cBShowGraphicsForm->TabIndex = 7;
			this->cBShowGraphicsForm->Text = L"Mostrar ventana gráfica";
			this->cBShowGraphicsForm->UseVisualStyleBackColor = true;
			this->cBShowGraphicsForm->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cBShowGraphicsForm_CheckedChanged);
			// 
			// groupGeneralOptions
			// 
			this->groupGeneralOptions->Controls->Add(this->txtMaxComputingTime);
			this->groupGeneralOptions->Controls->Add(this->cBLimitComputingTime);
			this->groupGeneralOptions->Controls->Add(this->numThreadsToUse);
			this->groupGeneralOptions->Controls->Add(this->cBUseMultithreading);
			this->groupGeneralOptions->Controls->Add(this->cBShowGraphicsForm);
			this->groupGeneralOptions->Controls->Add(this->btnResetNodeData);
			this->groupGeneralOptions->Location = System::Drawing::Point(12, 23);
			this->groupGeneralOptions->Name = L"groupGeneralOptions";
			this->groupGeneralOptions->Size = System::Drawing::Size(266, 171);
			this->groupGeneralOptions->TabIndex = 8;
			this->groupGeneralOptions->TabStop = false;
			this->groupGeneralOptions->Text = L"Opciones generales";
			// 
			// txtMaxComputingTime
			// 
			this->txtMaxComputingTime->Enabled = false;
			this->txtMaxComputingTime->Location = System::Drawing::Point(183, 89);
			this->txtMaxComputingTime->Name = L"txtMaxComputingTime";
			this->txtMaxComputingTime->Size = System::Drawing::Size(78, 20);
			this->txtMaxComputingTime->TabIndex = 12;
			// 
			// cBLimitComputingTime
			// 
			this->cBLimitComputingTime->AutoSize = true;
			this->cBLimitComputingTime->Location = System::Drawing::Point(6, 91);
			this->cBLimitComputingTime->Name = L"cBLimitComputingTime";
			this->cBLimitComputingTime->Size = System::Drawing::Size(171, 17);
			this->cBLimitComputingTime->TabIndex = 11;
			this->cBLimitComputingTime->Text = L"Limitar tiempo de computo (ms)";
			this->cBLimitComputingTime->UseVisualStyleBackColor = true;
			this->cBLimitComputingTime->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cBLimitComputingTime_CheckedChanged);
			// 
			// numThreadsToUse
			// 
			this->numThreadsToUse->Enabled = false;
			this->numThreadsToUse->Location = System::Drawing::Point(207, 64);
			this->numThreadsToUse->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
			this->numThreadsToUse->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numThreadsToUse->Name = L"numThreadsToUse";
			this->numThreadsToUse->Size = System::Drawing::Size(53, 20);
			this->numThreadsToUse->TabIndex = 9;
			this->numThreadsToUse->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numThreadsToUse->ValueChanged += gcnew System::EventHandler(this, &MainForm::numThreadsToUse_ValueChanged);
			// 
			// cBUseMultithreading
			// 
			this->cBUseMultithreading->AutoSize = true;
			this->cBUseMultithreading->Location = System::Drawing::Point(6, 65);
			this->cBUseMultithreading->Name = L"cBUseMultithreading";
			this->cBUseMultithreading->Size = System::Drawing::Size(194, 17);
			this->cBUseMultithreading->TabIndex = 8;
			this->cBUseMultithreading->Text = L"Usar multithreading en Fuerza Bruta";
			this->cBUseMultithreading->UseVisualStyleBackColor = true;
			this->cBUseMultithreading->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cBUseMultithreading_CheckedChanged);
			// 
			// groupOperationOptions
			// 
			this->groupOperationOptions->Controls->Add(this->btnSolve);
			this->groupOperationOptions->Controls->Add(this->comboBoxSolveMethod);
			this->groupOperationOptions->Controls->Add(this->lblSolveMethod);
			this->groupOperationOptions->Controls->Add(this->btnDeleteNode);
			this->groupOperationOptions->Controls->Add(this->comboBoxDeleteNode);
			this->groupOperationOptions->Controls->Add(this->lblDeleteNodeSelection);
			this->groupOperationOptions->Controls->Add(this->comboBoxInitNode);
			this->groupOperationOptions->Controls->Add(this->lblInitPoint);
			this->groupOperationOptions->Controls->Add(this->btnAddNode);
			this->groupOperationOptions->Controls->Add(this->txtNewNodeName);
			this->groupOperationOptions->Controls->Add(this->lblNewNodeName);
			this->groupOperationOptions->Location = System::Drawing::Point(12, 200);
			this->groupOperationOptions->Name = L"groupOperationOptions";
			this->groupOperationOptions->Size = System::Drawing::Size(266, 427);
			this->groupOperationOptions->TabIndex = 9;
			this->groupOperationOptions->TabStop = false;
			this->groupOperationOptions->Text = L"Operaciones";
			// 
			// btnSolve
			// 
			this->btnSolve->Location = System::Drawing::Point(80, 378);
			this->btnSolve->Name = L"btnSolve";
			this->btnSolve->Size = System::Drawing::Size(120, 43);
			this->btnSolve->TabIndex = 11;
			this->btnSolve->Text = L"Resolver";
			this->btnSolve->UseVisualStyleBackColor = true;
			this->btnSolve->Click += gcnew System::EventHandler(this, &MainForm::btnSolve_Click);
			// 
			// comboBoxSolveMethod
			// 
			this->comboBoxSolveMethod->FormattingEnabled = true;
			this->comboBoxSolveMethod->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
				L"Fuerza Bruta", L"Programación Dinámica",
					L"Ramificación y Acotamiento", L"Aproximado de Prim", L"Todos"
			});
			this->comboBoxSolveMethod->Location = System::Drawing::Point(12, 199);
			this->comboBoxSolveMethod->Name = L"comboBoxSolveMethod";
			this->comboBoxSolveMethod->Size = System::Drawing::Size(247, 21);
			this->comboBoxSolveMethod->TabIndex = 10;
			// 
			// lblSolveMethod
			// 
			this->lblSolveMethod->AutoSize = true;
			this->lblSolveMethod->Location = System::Drawing::Point(12, 183);
			this->lblSolveMethod->Name = L"lblSolveMethod";
			this->lblSolveMethod->Size = System::Drawing::Size(112, 13);
			this->lblSolveMethod->TabIndex = 9;
			this->lblSolveMethod->Text = L"Método de resolución:";
			// 
			// btnDeleteNode
			// 
			this->btnDeleteNode->Location = System::Drawing::Point(167, 127);
			this->btnDeleteNode->Name = L"btnDeleteNode";
			this->btnDeleteNode->Size = System::Drawing::Size(92, 39);
			this->btnDeleteNode->TabIndex = 8;
			this->btnDeleteNode->Text = L"Eliminar";
			this->btnDeleteNode->UseVisualStyleBackColor = true;
			this->btnDeleteNode->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteNode_Click);
			// 
			// comboBoxDeleteNode
			// 
			this->comboBoxDeleteNode->FormattingEnabled = true;
			this->comboBoxDeleteNode->Location = System::Drawing::Point(12, 145);
			this->comboBoxDeleteNode->Name = L"comboBoxDeleteNode";
			this->comboBoxDeleteNode->Size = System::Drawing::Size(121, 21);
			this->comboBoxDeleteNode->TabIndex = 7;
			// 
			// lblDeleteNodeSelection
			// 
			this->lblDeleteNodeSelection->AutoSize = true;
			this->lblDeleteNodeSelection->Location = System::Drawing::Point(9, 129);
			this->lblDeleteNodeSelection->Name = L"lblDeleteNodeSelection";
			this->lblDeleteNodeSelection->Size = System::Drawing::Size(73, 13);
			this->lblDeleteNodeSelection->TabIndex = 6;
			this->lblDeleteNodeSelection->Text = L"Eliminar nodo:";
			// 
			// comboBoxInitNode
			// 
			this->comboBoxInitNode->FormattingEnabled = true;
			this->comboBoxInitNode->Location = System::Drawing::Point(138, 78);
			this->comboBoxInitNode->Name = L"comboBoxInitNode";
			this->comboBoxInitNode->Size = System::Drawing::Size(121, 21);
			this->comboBoxInitNode->TabIndex = 5;
			// 
			// lblInitPoint
			// 
			this->lblInitPoint->AutoSize = true;
			this->lblInitPoint->Location = System::Drawing::Point(9, 81);
			this->lblInitPoint->Name = L"lblInitPoint";
			this->lblInitPoint->Size = System::Drawing::Size(78, 13);
			this->lblInitPoint->TabIndex = 4;
			this->lblInitPoint->Text = L"Nodo de inicio:";
			// 
			// lblNodeTable
			// 
			this->lblNodeTable->AutoSize = true;
			this->lblNodeTable->Location = System::Drawing::Point(284, 9);
			this->lblNodeTable->Name = L"lblNodeTable";
			this->lblNodeTable->Size = System::Drawing::Size(110, 13);
			this->lblNodeTable->TabIndex = 10;
			this->lblNodeTable->Text = L"Tabla de adyacencia:";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1327, 639);
			this->Controls->Add(this->lblNodeTable);
			this->Controls->Add(this->groupOperationOptions);
			this->Controls->Add(this->groupGeneralOptions);
			this->Controls->Add(this->dataGridNodesData);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"MA475 - TSP Solver - Grupo 4";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridNodesData))->EndInit();
			this->groupGeneralOptions->ResumeLayout(false);
			this->groupGeneralOptions->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numThreadsToUse))->EndInit();
			this->groupOperationOptions->ResumeLayout(false);
			this->groupOperationOptions->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private:
			void update_combobox_node_list()
			{
				comboBoxDeleteNode->Items->Clear();
				comboBoxInitNode->Items->Clear();
				comboBoxDeleteNode->Text = "";
				comboBoxInitNode->Text = "";
				for (int i = 0; i < dataGridNodesData->Columns->Count; ++i)
				{
					comboBoxDeleteNode->Items->Add(dataGridNodesData->Columns[i]->HeaderText);
					comboBoxInitNode->Items->Add(dataGridNodesData->Columns[i]->HeaderText);
				}

				if (comboBoxDeleteNode->Items->Count > 0)
					comboBoxDeleteNode->SelectedIndex = 0;
				if (comboBoxInitNode->Items->Count > 0)
					comboBoxInitNode->SelectedIndex = 0;
			}
			void reset_node_table()
			{
				dataGridNodesData->Rows->Clear();
				dataGridNodesData->Columns->Clear();
				dataGridNodesData->Refresh();
				comboBoxDeleteNode->Items->Clear();
				comboBoxInitNode->Items->Clear();

				comboBoxDeleteNode->Text = "";
				comboBoxInitNode->Text = "";
			}

			void add_node_to_table(bool use_custom_name)
			{
				int nodeCount = dataGridNodesData->Columns->Count;
				int newNode = nodeCount + 1;
				String^ nodeName;

				if (use_custom_name)
					nodeName = txtNewNodeName->Text != "" ? txtNewNodeName->Text : "Nodo " + newNode;
				else
					nodeName = "Nodo " + newNode;

				dataGridNodesData->Columns->Add(nodeName, nodeName);
				dataGridNodesData->Rows->Add();
				dataGridNodesData->Rows[nodeCount]->HeaderCell->Value = nodeName;
				dataGridNodesData[nodeCount, nodeCount]->ReadOnly = true;
				dataGridNodesData[nodeCount, nodeCount]->Value = "0";

				txtNewNodeName->Text = "Nodo " + (newNode + 1);
			}

			bool update_solver_nodes()
			{
				vector<vector<int>> nodeData;

				try
				{
					for (int i = 0; i < dataGridNodesData->Rows->Count; ++i)
					{
						vector<int> rowData;
						for (int j = 0; j < dataGridNodesData->Columns->Count; ++j)
						{
							int number = Convert::ToInt32(dataGridNodesData[i, j]->Value);

							if (number < 0)
								return false;

							rowData.push_back(number);
						}

						nodeData.push_back(rowData);
					}
				}
				catch (...)
				{
					return false;
				}

				solver->set_nodes(nodeData);

				return true;
			}
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		dataGridNodesData->RowHeadersWidthSizeMode = DataGridViewRowHeadersWidthSizeMode::AutoSizeToAllHeaders;
		numThreadsToUse->Maximum = thread::hardware_concurrency();
		comboBoxSolveMethod->SelectedIndex = 0;
	}

	private: System::Void btnAddNode_Click(System::Object^ sender, System::EventArgs^ e) {
		add_node_to_table(true);
		update_combobox_node_list();
	}
	private: System::Void btnResetNodeData_Click(System::Object^ sender, System::EventArgs^ e) {
		main_interface->reset_nodes();
		reset_node_table();
		update_combobox_node_list();
	}
private: System::Void btnSolveBruteForce_Click(System::Object^ sender, System::EventArgs^ e) {

}
private: System::Void cBShowGraphicsForm_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (cBShowGraphicsForm->Checked)
	{
		if (dataGridNodesData->Columns->Count > 0)
		{
			System::Windows::Forms::DialogResult result = MessageBox::Show("Activar el modo gráfico borrará la tabla actual. ¿Continuar?", "Aviso", MessageBoxButtons::OKCancel, MessageBoxIcon::Question);

			if (System::Windows::Forms::DialogResult::Cancel == result)
			{
				cBShowGraphicsForm->CheckedChanged -= gcnew System::EventHandler(this, &MainForm::cBShowGraphicsForm_CheckedChanged);
				cBShowGraphicsForm->Checked = false;
				cBShowGraphicsForm->CheckedChanged += gcnew System::EventHandler(this, &MainForm::cBShowGraphicsForm_CheckedChanged);
				return;
			}
		}
		reset_node_table();
		update_combobox_node_list();
		graphicsForm->Show();
		dataGridNodesData->Enabled = false;
		graphicsForm->Enabled = true;
		btnAddNode->Enabled = false;
		txtNewNodeName->Enabled = false;
	}
	else
	{
		main_interface->reset_nodes();
		reset_node_table();
		update_combobox_node_list();
		btnAddNode->Enabled = true;
		txtNewNodeName->Enabled = true;
		graphicsForm->Hide();
	}
}
private: System::Void cBUseMultithreading_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (cBUseMultithreading->Checked)
	{
		numThreadsToUse->Enabled = true;
		solver->use_multithreading = true;
		solver->threads = Convert::ToInt32(numThreadsToUse->Value);
	}
	else
	{
		solver->use_multithreading = false;
		solver->threads = 1;
	}
}
private: System::Void numThreadsToUse_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	solver->threads = Convert::ToInt32(numThreadsToUse->Value);
}

	   public:
		   void fill_node_table(vector<vector<int>> nodes)
		   {
			   reset_node_table();

			   for (int i = 0; i < nodes.size(); ++i)
			   {
				   add_node_to_table(false);
			   }

			   for (int i = 0; i < dataGridNodesData->Rows->Count; ++i)
			   {
				   vector<int> rowData;
				   for (int j = 0; j < dataGridNodesData->Columns->Count; ++j)
				   {
					   dataGridNodesData[i, j]->Value = nodes[i][j];
				   }
			   }

			   dataGridNodesData->Refresh();

			   update_combobox_node_list();
		   }

private: System::Void btnDeleteNode_Click(System::Object^ sender, System::EventArgs^ e) {
	if (comboBoxDeleteNode->Items->Count == 0)
		return;

	dataGridNodesData->Columns->RemoveAt(comboBoxDeleteNode->SelectedIndex);
	if (dataGridNodesData->Rows->Count > 0)
		dataGridNodesData->Rows->RemoveAt(comboBoxDeleteNode->SelectedIndex);
	main_interface->delete_node(comboBoxDeleteNode->SelectedIndex);
	update_solver_nodes();
	update_combobox_node_list();
}

	   private:
		   String^ get_results(String^ method_name)
		   {
			   vector<vector<int>> result_routes = solver->get_optimal_routes_result();
			   int result_route_cost = solver->get_optimal_routes_cost();
			   String^ result = "";

			   result += "	- - -	" + method_name + "	- - -	\r\n";

			   result += "Tiempo de cómputo: " + solver->get_computing_timme_taken().ToString() + " milisegundos.\r\n\r\n";

			   result += "Costo de la ruta optima: " + result_route_cost + "\r\n";

			   result += "Ruta óptima:\r\n";

			   for (int i = 0; i < result_routes.size(); ++i)
			   {
				   for (int j = 0; j < result_routes[i].size(); ++j)
				   {
					   if (j != result_routes[i].size() - 1)
						   result += (result_routes[i][j] + 1) + " -> ";
					   else
						   result += (result_routes[i][j] + 1);
				   }

				   result += "\r\n";
			   }

			   result += "\r\n\r\n";
			   return result;
		   }
		   void solve(int method_index)
		   {
			   if (!update_solver_nodes())
			   {
				   MessageBox::Show("Error al parsear la tabla, revise los datos ingresados.\nNo se permiten datos no numéricos o negativos.\nDatos vacíos son considerados cero.");
				   return;
			   }

			   String^ final_text = "";
			   switch (method_index)
			   {
			   case 0:
				   solver->solve_brute_force(comboBoxInitNode->SelectedIndex);
				   final_text = get_results(comboBoxSolveMethod->Items[method_index]->ToString());
				   break;
			   case 1:
				   solver->solve_dynamic_programming_method(comboBoxInitNode->SelectedIndex);
				   final_text = get_results(comboBoxSolveMethod->Items[method_index]->ToString());

				   break;
			   case 2:
				   solver->solve_branch_and_bound_method(comboBoxInitNode->SelectedIndex);
				   final_text = get_results(comboBoxSolveMethod->Items[method_index]->ToString());

				   break;
			   break;
			   case 3:
				   solver->solve_approximated_prim_method(comboBoxInitNode->SelectedIndex);
				   final_text = get_results(comboBoxSolveMethod->Items[method_index]->ToString());

				   break;
			   break;
			   case 4:
			   default:
				   solver->solve_brute_force(comboBoxInitNode->SelectedIndex);
				   final_text += get_results(comboBoxSolveMethod->Items[0]->ToString());

				   solver->solve_dynamic_programming_method(comboBoxInitNode->SelectedIndex);
				   final_text += get_results(comboBoxSolveMethod->Items[1]->ToString());

				   solver->solve_branch_and_bound_method(comboBoxInitNode->SelectedIndex);
				   final_text += get_results(comboBoxSolveMethod->Items[2]->ToString());

				   solver->solve_approximated_prim_method(comboBoxInitNode->SelectedIndex);
				   final_text += get_results(comboBoxSolveMethod->Items[3]->ToString());

				   break;
			   }
			   resultsForm = gcnew ResultsForm(final_text);

			   resultsForm->ShowDialog();
		   }
private: System::Void btnSolve_Click(System::Object^ sender, System::EventArgs^ e) {
	if (dataGridNodesData->Columns->Count < 3)
	{
		MessageBox::Show("Ingrese al menos 3 nodos");
		return;
	}

	try
	{
		if (cBLimitComputingTime->Checked)
		{
			solver->limit_computing_time = true;
			solver->limit_time = Convert::ToInt32(txtMaxComputingTime->Text);
		}
		else
		{
			solver->limit_computing_time = false;
			solver->limit_time = 0;
		}
	}
	catch (...)
	{
		MessageBox::Show("Revise el tiempo ingresado.");
		return;
	}

	solve(comboBoxSolveMethod->SelectedIndex);
}
private: System::Void cBLimitComputingTime_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (cBLimitComputingTime->Checked)
	{
		txtMaxComputingTime->Enabled = true;
	}
	else
	{
		txtMaxComputingTime->Enabled = false;
	}
}
};
}
