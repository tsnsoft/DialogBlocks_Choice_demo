/////////////////////////////////////////////////////////////////////////////
// Name:        mainform.cpp
// Purpose:     Реализация интерфейса для формирования состава салата
// Author:      Sergey Talipov
// Created:     17/03/2025 14:32:03
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"
#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "mainform.h"
#include "tsnsoft.xpm" // Иконка приложения

// Определение класса MainForm
IMPLEMENT_CLASS(MainForm, wxFrame)

BEGIN_EVENT_TABLE(MainForm, wxFrame)
EVT_CHOICE(ID_CHOICE, MainForm::OnChoiceSelected) // Обработчик события выбора элемента в списке выбора (Choice)
EVT_LISTBOX(ID_LISTBOX, MainForm::OnListboxSelected) // Обработчик события выбора элемента в списке выбора (ListBox)
EVT_RADIOBOX(ID_RADIOBOX, MainForm::OnRadioboxSelected) // Обработчик события выбора элемента в списке выбора (RadioBox)
EVT_CHECKBOX(ID_CHECKSALT, MainForm::OnChecksaltClick) // Обработчик события изменения состояния флажка (CheckBox)
EVT_CHECKBOX(ID_CHECKPIPER, MainForm::OnCheckpiperClick) // Обработчик события изменения состояния флажка (CheckBox)
EVT_BUTTON(ID_BUTTON, MainForm::OnButtonClick) // Обработчик события нажатия кнопки (Button)
END_EVENT_TABLE()

MainForm::MainForm() {
	Init();
}

MainForm::MainForm(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	Init();
	Create(parent, id, caption, pos, size, style);
}

bool MainForm::Create(wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style)
{
	if (!wxFrame::Create(parent, id, caption, pos, size, style)) {
		return false;
	}

	CreateControls(); // Создание элементов управления
	SetIcon(wxIcon(tsnsoft_xpm)); // Установка иконки приложения
	Centre(); // Центрирование окна на экране
	return true;
}

MainForm::~MainForm() {
}

void MainForm::Init() {
	ingredients.resize(5, wxEmptyString); // Инициализация массива ингредиентов
	m_choice = nullptr; // Инициализация переменной для списка выбора (Choice)
	m_listbox = nullptr; // Инициализация переменной для списка выбора (ListBox)	 
	m_radiobox = nullptr; // Инициализация переменной для списка выбора (RadioBox)
	m_checkbox_s = nullptr; // Инициализация переменной для флажка (CheckBox)
	m_checkbox_p = nullptr; // Инициализация переменной для флажка (CheckBox)
}

void MainForm::CreateControls()
{
	wxGridBagSizer* sizer = new wxGridBagSizer(10, 10);
	SetSizer(sizer);

	wxStaticText* label = new wxStaticText(this, wxID_STATIC, wxT("Состав салата:"), wxDefaultPosition, wxSize(100, -1));
	sizer->Add(label, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	ingredientsDisplay = new wxStaticText(this, ID_STATIC_INGREDIENTS, wxEmptyString, wxDefaultPosition, wxSize(350, 15));
	ingredientsDisplay->SetBackgroundColour(*wxWHITE);
	sizer->Add(ingredientsDisplay, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxArrayString baseIngredients = { wxT("Огурец"), wxT("Помидор"), wxT("Ананас"), wxT("Банан") };
	m_choice = new wxChoice(this, ID_CHOICE, wxDefaultPosition, wxDefaultSize, baseIngredients);
	sizer->Add(m_choice, wxGBPosition(1, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxArrayString citrusIngredients = { wxT("Апельсин"), wxT("Лимон"), wxT("Лайм") };
	m_listbox = new wxListBox(this, ID_LISTBOX, wxDefaultPosition, wxSize(170, -1), citrusIngredients, wxLB_SINGLE);
	sizer->Add(m_listbox, wxGBPosition(1, 1), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	wxArrayString dressings = { wxT("&Сметана"), wxT("&Масло") };
	m_radiobox = new wxRadioBox(this, ID_RADIOBOX, wxT("Заправка"), wxDefaultPosition, wxSize(170, -1), dressings, 2, wxRA_SPECIFY_ROWS);
	m_radiobox->SetSelection(0);
	sizer->Add(m_radiobox, wxGBPosition(1, 2), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	// Флажок "Посолить"
	m_checkbox_s = new wxCheckBox(this, ID_CHECKSALT, wxT("Посолить"));
	sizer->Add(m_checkbox_s, wxGBPosition(2, 0), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_checkbox_s->Bind(wxEVT_CHECKBOX, &MainForm::OnChecksaltClick, this);

	// Флажок "Поперчить"
	m_checkbox_p = new wxCheckBox(this, ID_CHECKPIPER, wxT("Поперчить"));
	sizer->Add(m_checkbox_p, wxGBPosition(2, 1), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);
	m_checkbox_p->Bind(wxEVT_CHECKBOX, &MainForm::OnCheckpiperClick, this);

	wxButton* resetButton = new wxButton(this, ID_BUTTON, wxT("Сброс"));
	sizer->Add(resetButton, wxGBPosition(2, 2), wxGBSpan(1, 1), wxALIGN_CENTER_VERTICAL | wxALL, 5);

	sizer->SetSizeHints(this);
}

// Обновление отображения ингредиентов
void MainForm::UpdateIngredientsDisplay()
{
	if (ingredients.empty()) return; // Проверка наличия элементов в массиве ингредиентов
	wxString result; // Результирующая строка
	for (const auto& ingredient : ingredients) { // Перебор элементов массива ингредиентов
		if (!ingredient.IsEmpty()) { // Проверка наличия элемента
			if (!result.IsEmpty()) result += wxT(", "); // Добавление разделителя
			result += ingredient; // Добавление ингредиента
		}
	}
	ingredientsDisplay->SetLabel(result); // Установка результата в элемент управления
}

// Обработчик события выбора элемента в списке выбора (Choice)
void MainForm::OnChoiceSelected(wxCommandEvent& event) {
	if (m_choice) ingredients[0] = m_choice->GetStringSelection();
	UpdateIngredientsDisplay();
}

// Обработчик события выбора элемента в списке выбора (ListBox)
void MainForm::OnListboxSelected(wxCommandEvent& event) {
	if (m_listbox) ingredients[1] = m_listbox->GetStringSelection();
	UpdateIngredientsDisplay();
}

// Обработчик события выбора элемента в списке выбора (RadioBox)
void MainForm::OnRadioboxSelected(wxCommandEvent& event) {
	if (m_radiobox) ingredients[2] = m_radiobox->GetStringSelection(); // Установка значения в массиве ингредиентов
	UpdateIngredientsDisplay(); // Обновление отображения ингредиентов
}

// Обработчик события изменения состояния флажка (CheckBox) "Посолить"
void MainForm::OnChecksaltClick(wxCommandEvent& event)
{
	if (m_checkbox_s) { // Проверка наличия флажка
		ingredients[3] = m_checkbox_s->IsChecked() ? wxT("Посолить") : wxEmptyString; // Установка значения в массиве ингредиентов
		UpdateIngredientsDisplay(); // Обновление отображения ингредиентов
	}
}

// Обработчик события изменения состояния флажка (CheckBox) "Поперчить"
void MainForm::OnCheckpiperClick(wxCommandEvent& event)
{
	if (m_checkbox_p) { // Проверка наличия флажка
		ingredients[4] = m_checkbox_p->IsChecked() ? wxT("Поперчить") : wxEmptyString; // Установка значения в массиве ингредиентов	
		UpdateIngredientsDisplay(); // Обновление отображения ингредиентов
	}
}

// Обработчик события нажатия кнопки (Button)
void MainForm::OnButtonClick(wxCommandEvent& event)
{
	std::fill(ingredients.begin(), ingredients.end(), wxEmptyString); // Очистка массива ингредиентов
	if (m_checkbox_s) m_checkbox_s->SetValue(false); // Сброс флажка "Посолить"
	if (m_checkbox_p) m_checkbox_p->SetValue(false); // Сброс флажка "Поперчить"
	UpdateIngredientsDisplay(); // Обновление отображения ингредиентов
}

/*
 * Get bitmap resources
 */

wxBitmap MainForm::GetBitmapResource(const wxString& name)
{
	// Bitmap retrieval
////@begin MainForm bitmap retrieval
	wxUnusedVar(name);
	return wxNullBitmap;
	////@end MainForm bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon MainForm::GetIconResource(const wxString& name)
{
	// Icon retrieval
////@begin MainForm icon retrieval
	wxUnusedVar(name);
	if (name == wxT("tsnsoft.xpm"))
	{
		wxIcon icon(tsnsoft_xpm);
		return icon;
	}
	return wxNullIcon;
	////@end MainForm icon retrieval
}
