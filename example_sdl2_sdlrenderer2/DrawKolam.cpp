#include "DrawKolam.h"
#include "Texture.h"

#include "IconsFontAwesome.h"
int pev = 0;
int PREV_TOTAL_BUTTONS = 0;
ImVec4 BGcolor = ImVec4(0.796078f, 0.407843f, 0.262745f, 1.00f);
ImVec4 FRcolor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
bool DrawKolam::Init() {
	bool pass = true;
	if(!InitImGui()) {
			printf("In draw kolam class imgui not initiliazed!");
			pass = false;
	}
	if (!InitTextures()) {
		printf("In draw kolam class texture not initiliazed!");
		pass = false;
	}
	else {

		int * CurrSprite;
		if (PREV_TOTAL_BUTTONS > TOTAL_BUTTONS) {
			PREV_TOTAL_BUTTONS = TOTAL_BUTTONS;
		}
		if(PREV_TOTAL_BUTTONS)
		{
			CurrSprite=new int[PREV_TOTAL_BUTTONS];
			for (int i=0; i<PREV_TOTAL_BUTTONS; i++ )
			{
				CurrSprite[i] = butts[i].GetSprite();	
			}
		}
		butts = new KolamButton[TOTAL_BUTTONS];
		DrawButtons();

		if(PREV_TOTAL_BUTTONS)
		{
			for (int i=0; i<PREV_TOTAL_BUTTONS; i++ )
			{
				butts[i].ChangeSprite(CurrSprite[i]);	
			}
		}
	}
	return pass;
	
}

void DrawKolam::Update() {
	//SDL_SetRenderDrawColor(gRenderer, 0xCB, 0x68, 0x43, 0xFF);
	SDL_SetRenderDrawColor(gRenderer, (Uint8)(BGcolor.x * 255), (Uint8)(BGcolor.y * 255), (Uint8)(BGcolor.z * 255), (Uint8)(BGcolor.w * 255));

	//SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gRenderer);

	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImVec2 ButtonSize = ImVec2(50, 50);

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x,70));
	ImGui::Begin("Titlebar", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	if(ImGui::Button(ICON_FA_BARS,ButtonSize)){ Mix_PlayChannel(-1, buttSound, 0); }
	ImGui::SameLine();
	ImGui::PushFont(BoldFont);
	ImGui::Text(NAME);
	ImGui::PopFont();
	ImGui::End();
	

	//ImGui::ShowDemoWindow();
	gFont->Scale = 0.8;
	ImGui::PushFont(gFont);
	ImGui::SetNextWindowPos(ImVec2(0, 70));
	ImGui::SetNextWindowSize(ImVec2(70, ImGui::GetIO().DisplaySize.y-70));
	ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	//RESIZE 
	if (ImGui::Button(ICON_FA_TABLE_CELLS,ButtonSize))
	{
		Mix_PlayChannel(-1, buttSound, 0);
		ImGui::OpenPopup("Resize");
	}
	ImGui::SetItemTooltip("Resize");
	
	int y = ImGui::GetCursorPos().y;
	ImGui::SetNextWindowPos(ImVec2(70, y), ImGuiCond_Appearing, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginPopup("Resize")) {
		//ROWS
		static int R=ROWS,C=COLS;

		ImGui::Text("No. of Rows:");
		ImGui::SameLine();

		int y = ImGui::GetCursorPosY();
		ImGui::SetCursorPos(ImVec2(177, y));
		ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
		ImGui::PushItemWidth(100);

		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{R = R - 1 > 0 ? R - 1 : 1; Mix_PlayChannel(-1, buttSound, 0);}

		float spacing = 15;
		ImGui::SameLine(0.0f, spacing);
		ImGui::Text("%d", R);
		ImGui::SameLine(0.0f, spacing);

		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{R = R + 1 < 10 ? R + 1 : 9; Mix_PlayChannel(-1, buttSound, 0);}

		//ROWS = rows;

		//COLUMNS
		ImGui::PushID(1);
		ImGui::Text("No. of Columns:");
		ImGui::SameLine();
		//printf("%f\n", ImGui::GetCursorPosX());

		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{C = C - 1 > 0 ? C - 1 : 1; Mix_PlayChannel(-1, buttSound, 0);}

		ImGui::SameLine(0.0f, spacing);
		ImGui::Text("%d", C);
		ImGui::SameLine(0.0f, spacing);

		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			C = C + 1 < 10 ? C +1 : 9; Mix_PlayChannel(-1, buttSound, 0);
		}
		ImGui::PopItemFlag();
		ImGui::PopID();

		BoldFont->Scale = 0.6;
		ImGui::PushFont(BoldFont);
		ImGui::Indent(90);
		if (ImGui::Button(" Okay! ",ImVec2(100,35))) {
			Mix_PlayChannel(-1, buttSound, 0);
			if (R != ROWS || C != COLS) {
				ROWS = R; COLS = C;
				Init();
			}
			ImGui::CloseCurrentPopup();
		}
		ImGui::PopFont();
		BoldFont->Scale = 1;
		ImGui::EndPopup();
	}


	//BRUSH SIZE
	if (ImGui::Button(ICON_FA_BRUSH, ButtonSize))
	{
		Mix_PlayChannel(-1, buttSound, 0);
		ImGui::OpenPopup("Bursh Size Popup");
	}
	ImGui::SetItemTooltip("Brush Size");

	y = ImGui::GetCursorPos().y;
	ImGui::SetNextWindowPos(ImVec2(70, y), ImGuiCond_Appearing, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginPopup("Bursh Size Popup"))
	{
		
		int thick = THICK;
		ImGui::ColorEdit4("clear color", (float*)&FRcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel); // Edit 3 floats representing a color
		ImGui::SameLine();
		ImGui::PushItemWidth(180);
		ImGui::SliderInt("##", &thick, 1.0f, MaxTHICK);
		THICK = thick;

		ImGui::EndPopup();
	}


	//BACKGROUND COLOR
	if (ImGui::Button(ICON_FA_DROPLET, ButtonSize))
	{
		Mix_PlayChannel(-1, buttSound, 0);
		ImGui::OpenPopup("Background Color");
	}
	ImGui::SetItemTooltip("Background Color");
	y = ImGui::GetCursorPos().y;
	ImGui::SetNextWindowPos(ImVec2(70, y), ImGuiCond_Appearing, ImVec2(0.0f, 0.0f));
	if (ImGui::BeginPopup("Background Color"))
	{
		ImGui::ColorPicker4("clear color", (float*)&BGcolor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel); 
		ImGui::EndPopup();
	}
	
	//OPEN FOLDER
	/*
	if (ImGui::Button(ICON_FA_FOLDER_OPEN, ButtonSize))
	{
		Mix_PlayChannel(-1, buttSound, 0);
	}
	ImGui::SetItemTooltip("Open");*/

	//EXPORT
	static int a;
	if (ImGui::Button(ICON_FA_FILE_ARROW_DOWN, ButtonSize))
	{
		Mix_PlayChannel(-1, buttSound, 0);
		a = ExportKolam();
		ImGui::OpenPopup("Saving Report");
		
	}
	ImGui::SetItemTooltip("Save");

	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Saving Report", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
		if (a) ImGui::Text("Saved to the current working directory");
		else ImGui::Text("Couldn't Export the Design");

		float popupWidth = ImGui::GetWindowWidth();
		ImGui::Indent(popupWidth/2-100);
		if (ImGui::Button("Okay!", ImVec2(200, 0))) {
			ImGui::CloseCurrentPopup();
			Mix_PlayChannel(-1, buttSound, 0);
		}
		ImGui::EndPopup();
	}

	// DELETE
	if (ImGui::Button(ICON_FA_TRASH_CAN, ButtonSize))
	{
		ImGui::OpenPopup("Delete it?!");
		Mix_PlayChannel(-1, buttSound, 0);
	}
	ImGui::SetItemTooltip("Delete");
	
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	if (ImGui::BeginPopupModal("Delete it?!", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("The beautiful drawing will be deleted!\n Do you want to proceed for sure?");
		ImGui::Separator();

		if (ImGui::Button("Yes! Delete it", ImVec2(200, 0))) {
			ImGui::CloseCurrentPopup(); 
			Mix_PlayChannel(-1, buttSound, 0);
			ClearAll();}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("No Way!", ImVec2(200, 0))) { ImGui::CloseCurrentPopup();Mix_PlayChannel(-1, buttSound, 0);}
		ImGui::EndPopup();
	}
	
	ImGui::PopFont();
	//gFont->Scale *= 1.66;
	ImGui::End();

}

void DrawKolam::Render() {
	InitTextures();
	ImGui::Render();
	
	RenderButtons();
	
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), gRenderer);

}

void DrawKolam::HandleEvent(SDL_Event *e){
	ImGui_ImplSDL2_ProcessEvent(e);

	//To prevent things from clicking in background when Pop Up is active
	if (io->WantCaptureMouse || io->WantCaptureKeyboard) {
		return;
	}

	buttonType place;
	int i;
	butts[pev].ChangeState(KolamButton::Outside);
	if (CheckInside(place)) {
		i = ActiveButtonID(place);
		butts[i].ChangeState(KolamButton::Inside);
		if (e->type == SDL_MOUSEBUTTONDOWN) {
			Mix_PlayChannel(-1, buttSound, 0);
			butts[i].ChangeSprite();
			butts[i].ChangeState(KolamButton::Pressed);
		}
		pev = i;
	}
}

bool ExportKolam() {
	
	//Texture Final;
	// 1) make  a local variable, remove from texture.h and .cpp
	// 2) remove the comments from the if of render function in texture class
	int borders = 50;
	if (!Final.CreateBlankSheet(4*SPACE *ROWS +2*borders, 4*SPACE *COLS +2*borders, SDL_TEXTUREACCESS_TARGET)) {
		printf("Failed to make dot sprite\n");
		return false;
	}
	else {
		Final.SetAsRenderTarget();
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(BGcolor.x * 255), (Uint8)(BGcolor.y * 255), (Uint8)(BGcolor.z * 255), (Uint8)(BGcolor.w * 255));

		SDL_RenderClear(gRenderer);
		SDL_SetRenderDrawColor(gRenderer, (Uint8)(FRcolor.x * 255), (Uint8)(FRcolor.y * 255), (Uint8)(FRcolor.z * 255), (Uint8)(FRcolor.w * 255));
		
		for (int ri = 0, x = 2 * SPACE + borders, i =0; ri < COLS; ri++, x += 4 * SPACE) {
			for (int ci = 0, y = 2 * SPACE + borders;ci < ROWS; ci++, i += 4, y += 4 * SPACE) {
			//Left
			if(butts[i].GetSprite()!=2)
			sheetLR.Render(x - 2 * SPACE, y - SPACE, &ImgLR[butts[i].GetSprite()], SPACE + THICK+1, 2*SPACE, 180.0);
			//bottom
			if (butts[i+1].GetSprite() != 2)
			sheetUD.Render(x - 2 * SPACE, y + SPACE, &ImgUD[butts[i+1].GetSprite()], 4*SPACE, SPACE, 180.0);
			//Right
			if (butts[i+2].GetSprite() != 2)
			sheetLR.Render(x + SPACE -THICK, y - SPACE, &ImgLR[butts[i+2].GetSprite()], SPACE + THICK+1, 2 * SPACE, 0);
			//Top
			if (butts[i+3].GetSprite() != 2)
			sheetUD.Render(x - 2 * SPACE, y - 2 * SPACE, &ImgUD[butts[i + 3].GetSprite()], 4 * SPACE, SPACE, 0);

			dot.Render(x - SPACE / 6, y - SPACE / 6);
			
			}
		}
		/*switch (place) {
		case right: case left:
			sheetLR.Render(pos.x, pos.y, &ImgLR[cur], bw, bh, (place - 1) * 90.0); break;
		case bottom: case top:
			sheetUD.Render(pos.x, pos.y, &ImgUD[cur], bw, bh, place * 90.0);break;
		}*/

		SDL_SetRenderTarget(gRenderer, NULL);

		
		return Final.SaveImage();



	}

}


void GlobalDec() {
	int wd = SCREEN_WIDTH - 70;
	int ht = SCREEN_HEIGHT - 70;
	SPACE = std::min(wd/ (4 * COLS), ht/ (4 * ROWS));
	OffsetX = (wd - 4 * SPACE * COLS) / 2+70;
	OffsetY = (ht - 4 * SPACE * ROWS) / 2+70;

	TOTAL_BUTTONS = 4 * ROWS * COLS;
	MaxTHICK = 0.8*SPACE;// 2(2-root(2))*thick -> where the outer circle will touch the boundary
	if(THICK == 0.0)
		THICK = 0.3 * SPACE;
	else
		THICK = SDL_clamp(THICK, 1.0f, MaxTHICK);
}

void RenderButtons() {

	int a = dot.GetWidth();
	for (int ri = 0, x = 2 * SPACE + OffsetX, i = 0; ri < COLS; ri++, x += 4 * SPACE) {
		for (int ci = 0, y = 2 * SPACE + OffsetY;ci < ROWS; ci++, i += 4, y += 4 * SPACE) {

			dot.Render(x - a / 2, y - a / 2);

			//0->left 1-> bottom 2-> right 3->top
			butts[i].Render(BGcolor);
			butts[i + 2].Render(BGcolor);
			butts[i + 1].Render(BGcolor);
			butts[i + 3].Render(BGcolor);

		}
	}
}

void DrawButtons() {
	/*Freeing the existing buttons
	for (int i = 0; i < TOTAL_BUTTONS; i++) {
		butts[i].~KolamButton();
	}
	delete[] butts;
	butts = NULL;

	//Decl*/
	//KolamButton* butts;

	int a = dot.GetWidth();
	for (int ri = 0, x = 2 * SPACE + OffsetX, i = 0; ri < COLS; ri++,x += 4 * SPACE) {
		for (int ci = 0, y = 2 * SPACE + OffsetY;ci < ROWS; ci++, i += 4,  y += 4 * SPACE) {
		
			dot.Render(x - a / 2, y - a / 2);

			//0->left 1-> bottom 2-> right 3->top
			butts[i].SetPosition(x - 2 * SPACE, y - SPACE, left);
			butts[i + 2].SetPosition(x + SPACE - THICK, y - SPACE, right);
			butts[i + 1].SetPosition(x - 2 * SPACE, y + SPACE, bottom);
			butts[i + 3].SetPosition(x - 2 * SPACE, y - 2 * SPACE, top);

		}
	}
}

int ActiveButtonID(buttonType &place) {
	int x, y, i;
	SDL_GetMouseState(&x, &y);
	int N = ROWS * ((x - OffsetX) / (4 * SPACE)) + ((y - OffsetY) / (4 * SPACE));
	switch (place)
	{
	case left:
		i = 4 * N;
		break;
	case bottom:
		i = 4 * N + 1;
		break;
	case right:
		i = 4 * N + 2;
		break;
	case top:
		i = 4 * N + 3;
		break;
	}
	return i;
}

int CheckInside(buttonType &place) {

	int x, y, xin, yin;
	int inn = 0;

	SDL_GetMouseState(&x, &y);

	if (x<OffsetX || x>(OffsetX + COLS * 4 * SPACE)) {
		return 0;
	}
	if (y<OffsetY || y>(OffsetY + ROWS * 4 * SPACE)) {
		return 0;
	}
	yin = (y - OffsetY - (4 * SPACE) * ((y - OffsetY) / (4 * SPACE))) / SPACE;

	if (yin == 0) {
		place = top;
		return 1;
	}
	else if (yin == 3) {
		place = bottom;
		return 1;
	}

	xin = (x - OffsetX - (4 * SPACE) * ((x - OffsetX) / (4 * SPACE)));
	if (xin <= SPACE + THICK) {
		place = left;
		return 1;
	}
	else if (3 * SPACE - THICK <= xin) {
		place = right;
		return 1;
	}
	return inn;
}

void ClearAll() {
	for (int i = 0;i < TOTAL_BUTTONS;i++) {
		butts[i].ChangeSprite(2);
		//butts[i].Render();
	}
		
}

bool InitImGui() {
	
	
	ImGui::GetStyle() = ImGuiStyle();
	style = &ImGui::GetStyle();

	style->Colors[ImGuiCol_Button] = ImVec4(((float)0xCC / (float)255), ((float)0x6B / (float)255), ((float)0x47 / (float)255), 1.f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(((float)0xCC / (float)255), ((float)0x4A / (float)255), ((float)0x19 / (float)255), 1.f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(((float)0x99 / (float)255), ((float)0x41 / (float)255), ((float)0x1F / (float)255), 1.f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(((float)0x99 / (float)255), ((float)0x67 / (float)255), ((float(0x54) / (float)255)), 1.f);
	
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(((float)0x99 / (float)255), ((float)0x4D / (float)255), ((float(0x2C) / (float)255)), 1.f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(((float)0x99 / (float)255), ((float)0x4D / (float)255), ((float)0x2C / (float)255), 1.f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(((float)0xCC / (float)255), ((float)0x6B / (float)255), ((float)0x47 / (float)255), 1.f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(((float)0xCC / (float)255), ((float)0x4A / (float)255), ((float)0x19 / (float)255), 1.f);


	style->WindowPadding = ImVec2(10, 10);
	style->FramePadding = ImVec2(10, 5);

	style->ItemSpacing = ImVec2(20, 20);
	style->ItemInnerSpacing = ImVec2(30, 30);


	style->WindowRounding = 0;
	style->FrameRounding = 15;
	style->GrabRounding = 10;
	return true;
}

bool InitTextures() {
	bool pass = true;
	PREV_TOTAL_BUTTONS = TOTAL_BUTTONS;
	GlobalDec();
	if (MakeDot(FRcolor) && MakeSheetLR(FRcolor) && MakeSheetUD(FRcolor))
	{
		
		//DrawButtons();
	}
	else {
		printf("Textures not made");
		pass = false;
	}
	return pass;
}