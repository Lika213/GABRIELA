#include "ExG4DetectorConstruction01.hh"
#include "ExG4DetectorSD.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Material.hh"
#include "G4Material.hh"
// Менеджер предопределенных материалов
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
// Подключаем систему едениц измерения, что бы пользоваться еденицами cm, MeV.
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
// Конструктор класса объявления материалов и геометрии всей моделируемой системы
ExG4DetectorConstruction01::ExG4DetectorConstruction01()
    : G4VUserDetectorConstruction()
{ }

// Деструктор
ExG4DetectorConstruction01::~ExG4DetectorConstruction01()
{ }

// Функция определения материалов и геометрии всей системы,
// должна возвращать физический объем - ссылку на экземпляр класса G4VPhysicalVolume
// Геометрию проектировать будем следующую: пучок протонов попадает на мишень
// вольфрамовый лист толщиной 1 мм, а за мишенью поставим детектор
// таких же размеров, он будет регистрировать что в него попало.
G4VPhysicalVolume* ExG4DetectorConstruction01::Construct()
{
    //G4double det_XY = 80.08 * mm, det_Z = 70. * mm;//Ge

    // Определяем размеры детектора
    G4double det_sizeXY = 40.08 * mm, det_sizeZ = 70. * mm;//Ge
    G4double DSSD_sizeX = 100 * mm, DSSD_sizeY = 100 * mm, DSSD_sizeZ = 0.5 * mm, DSSD_sizeZ_2 = 60 * mm;//DSSD
    G4double wall_sizeX = 1. * mm, wall_sizeY = 92 * mm, wall_sizeZ = 70. * mm;// вертикальная Al перегородка
    G4double wall2_sizeX = 46. * mm, wall2_sizeY = 1 * mm, wall2_sizeZ = 70. * mm;// горизонтальная Al перегородка
    G4double glass_sizeXY = 9. * cm, glass_sizeZ = 1. * mm;// Алюминиевый стакан  
    //G4double window_sizeXY = 9. * cm, window_sizeZ = 0.6 * mm;//Углеродное входное окно толщиной 0,6мм . 
    /*//Coordinates
    G4double DSSD_X = 0 * mm, DSSD_Y = 0 * mm, DSSD_Z = 0 * mm;//DSSD
    G4double glass_X = 0 * mm, glass_Y = 0. * mm, glass_Z = 41.75 * mm;;// Алюминиевый стакан
    G4double window_X = 0 * mm, window_Y = 0. * mm, window_Z = 42.55 * mm;//Углеродное входное окно толщиной 0,6мм . 
    G4double X = 20.54 * mm, Y = 20.54 * mm, Z = 79.05 * mm; // coord det_GE
    G4double Al_verX = 0 * mm, Al_verY = 0 * mm, Al_verZ = Z; //вертикальная Al перегородка
    G4double Al_gorlX = 23 * mm, Al_gorlY = 0 * mm, Al_gorlZ = Z;//  горизонтальная Al перегородка*/

    //41mm from DSSD to PHGE
    G4double DSSD_X = 0 * mm, DSSD_Y = 0 * mm, DSSD_Z = 32.5 * mm;//DSSD
    G4double glass_X = 0 * mm, glass_Y = 0. * mm, glass_Z = 39. * mm;;// Алюминиевый стакан
    //G4double window_X = 0 * mm, window_Y = 0. * mm, window_Z = 39.75 * mm;//Углеродное входное окно толщиной 0,6мм . 
    G4double X = 20.54 * mm, Y = 20.54 * mm, Z = 75.5 * mm; // coord det_GE
    G4double Al_verX = 0 * mm, Al_verY = 0 * mm, Al_verZ = Z; //вертикальная Al перегородка
    G4double Al_gorlX = 23.5 * mm, Al_gorlY = 0 * mm, Al_gorlZ = Z;//  горизонтальная Al перегородка
   
    /// YYYYYY
    G4double DSSD_X_2 = 0 * mm, DSSD_Y_2 = 52.75 * mm, DSSD_Z_2 = 0.5* mm;//DSSD
    G4double glass_X_2 = 0 * mm, glass_Y_2 = 80.6 * mm, glass_Z_2 = 0 * mm;;// Алюминиевый стакан
    //G4double window_X_2 = 0 * mm, window_Y_2 = 81.3 * mm, window_Z_2 = 0 * mm;//Углеродное входное окно толщиной 0,6мм . 
    G4double X_2 = 20.54 * mm, Y_2 = 117.1 * mm, Z_2 = 20.54 * mm; // coord det_GE
    G4double Al_verX_2 = 0 * mm, Al_verY_2 = Y_2, Al_verZ_2 = 0*mm; //вертикальная Al перегородка
    G4double Al_gorlX_2 = 23.5 * mm, Al_gorlY_2 = Y_2, Al_gorlZ_2 = 0 *mm;

    G4double det_sizeX_2 = 40.08 * mm, det_sizeY_2 = 70.0 * mm, det_sizeZ_2 = 40.08 * mm;//Ge
    G4double wall_sizeX_2 = 1. * mm, wall_sizeY_2 = 70. * mm, wall_sizeZ_2 = 92. * mm;// вертикальная Al перегородка
    G4double wall2_sizeX_2 = 46. * mm, wall2_sizeY_2 = 70 * mm, wall2_sizeZ_2 = 1. * mm;// горизонтальная Al перегородка
    G4double glass_sizeX_2 = 90. * mm, glass_sizeY_2 = 1. * mm, glass_sizeZ_2 = 90. * mm;// Алюминиевый стакан  
   // G4double window_sizeX_2 = 90. * mm, window_sizeY_2 = 0.6 * mm, window_sizeZ_2 = 90. * mm;//Углеродное входное окно толщиной 0,6мм . 

    //////////// XXXXXXXXXXXX

    G4double glass_X_4 = 80.6 * mm, glass_Y_4 = 0 * mm, glass_Z_4 = 0 * mm;;// Алюминиевый стакан
   // G4double window_X_4 = 81.3 * mm, window_Y_4 = 0 * mm, window_Z_4 = 0 * mm;//Углеродное входное окно толщиной 0,6мм . 
    G4double X_4 = 117.1 * mm, Y_4 = 20.54 * mm, Z_4 = 20.54 * mm; // coord det_GE
    G4double Al_verX_4 = X_4, Al_verY_4 = 0 * mm, Al_verZ_4 = 0 * mm; //вертикальная Al перегородка
    G4double Al_gorlX_4 = X_4, Al_gorlY_4 = 23.5 * mm, Al_gorlZ_4 = 0 * mm;

    G4double det_sizeX_4 = 70.0 * mm, det_sizeY_4 = 40.08 * mm, det_sizeZ_4 = 40.08 * mm;//Ge
    G4double wall_sizeX_4 = 70. * mm, wall_sizeY_4 = 1. * mm, wall_sizeZ_4 = 92. * mm;// вертикальная Al перегородка
    G4double wall2_sizeX_4 = 70. * mm, wall2_sizeY_4 = 46. * mm, wall2_sizeZ_4 = 1. * mm;// горизонтальная Al перегородка
    G4double glass_sizeX_4 = 1. * mm, glass_sizeY_4 = 90. * mm, glass_sizeZ_4 = 90. * mm;// Алюминиевый стакан  
   // G4double window_sizeX_4 = 0.6 * mm, window_sizeY_4 = 90. * mm, window_sizeZ_4 = 90. * mm;//Углеродное входное окно толщиной 0,6мм . 

    // Материал детектора, здесь выбираем вольфрам
    G4NistManager* nist = G4NistManager::Instance();
    //G4Element* Na = nist->FindOrBuildElement(11);
    //G4Element* I = nist->FindOrBuildElement(53);
    //G4Material* NaI = new G4Material("NaI", 3.67 * g / cm3, 2);
    //NaI->AddElement(Na, 1);
    //NaI->AddElement(I, 1);
    G4Material* det_mat = nist->FindOrBuildMaterial("G4_Ge");
    G4Material* DSSD_mat = nist->FindOrBuildMaterial("G4_Si");
    G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al");
    G4Material* C_mat = nist->FindOrBuildMaterial("G4_C");

    G4Element* C = nist->FindOrBuildElement(6);
    G4Element* F = nist->FindOrBuildElement(9);
    G4Material* C2F4 = new G4Material("C2F4", 2.21 * g / cm3, 2);
    C2F4->AddElement(C, 2);
    C2F4->AddElement(F, 4);


    // Опция для включения/выключения проверки перекрытия объемов
    G4bool checkOverlaps = true;

    // World
    G4double world_sizeXY = 40 * cm;
    G4double world_sizeZ = 40 * cm;
    //G4double universe_mean_density = 7.e-30 * g / cm3;
    // Выбор материала для мира из предопределенных в Geant4, для зала берем воздух
    G4Material* G4_Vacuum = new G4Material("G4_Vacuum", 1., 1.01 * g / mole, universe_mean_density, kStateGas, 2.73 * kelvin, 3.e-18 * pascal);

    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Vacuum");

    //WORLD
    auto solidWorld = new G4Box("World", 0.5 * world_sizeXY, 0.5 * world_sizeXY, 0.5 * world_sizeZ);     //its size, его размеры
    auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");
    auto physWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld,"World",0,false, 0,checkOverlaps);        //overlaps checking, флаг проверки перекрытия объемов


  /*  ///BIG DET
    G4Box* solidDet = new G4Box("Detector",0.5 * det_XY, 0.5 * det_XY, 0.5 * det_Z);
    G4LogicalVolume* logicDet =new G4LogicalVolume(solidDet,det_mat,"Detector");
    new G4PVPlacement(0,G4ThreeVector(0.*mm,0.*mm, Z),logicDet,"Detector",logicWorld,false,0,checkOverlaps);    */      

    // Детектор, для него также используем параллелепипед 
    // NE
    G4Box* solidDet = new G4Box("Detector",0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ);
    G4LogicalVolume* logicDet =new G4LogicalVolume(solidDet, det_mat, "Detector");
    new G4PVPlacement(0,G4ThreeVector(-X, Y, Z),logicDet,"Detector",logicWorld,false, 0,checkOverlaps);          //overlaps checking, флаг проверки перекрытия объемов

    //det NW
    G4Box* solidDetNW =new G4Box("Detector",0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ);
    G4LogicalVolume* logicDetNW = new G4LogicalVolume(solidDetNW,det_mat,  "Detector");
    new G4PVPlacement(0, G4ThreeVector(X, Y, Z), logicDetNW, "Detector", logicWorld, false, 0, checkOverlaps);

    //DET SW
    G4Box* solidDetSW = new G4Box("Detector", 0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ); 
    G4LogicalVolume* logicDetSW = new G4LogicalVolume(solidDetSW, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X, -Y, Z), logicDetSW, "Detector", logicWorld, false, 0, checkOverlaps);

    //DET SE
    G4Box* solidDetSE = new G4Box("Detector", 0.5 * det_sizeXY, 0.5 * det_sizeXY, 0.5 * det_sizeZ); //its size, размеры
    G4LogicalVolume* logicDetSE = new G4LogicalVolume(solidDetSE, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X, -Y, Z), logicDetSE, "Detector", logicWorld, false, 0, checkOverlaps);

    /*G4VisAttributes* DetVisAtt
        = new G4VisAttributes(G4Colour(1.0, 0.0, 0.50));
    logicDetSW->SetVisAttributes(DetVisAtt);*/
    
    // Al перегородка 1 мм
    G4Box* solidwall =new G4Box("Alwall",0.5 * wall_sizeX, 0.5 * wall_sizeY, 0.5 * wall_sizeZ);
    G4LogicalVolume* logicwall =new G4LogicalVolume(solidwall, Al_mat,"Alwall");         //its name, его имя
    new G4PVPlacement(0,G4ThreeVector(Al_verX, Al_verY, Al_verZ),logicwall,"Alwall",logicWorld,false, 0,checkOverlaps);

    // Al перегородка 1 мм

    G4Box* solidwall2 = new G4Box("Alwall2",0.5 * wall2_sizeX, 0.5 * wall2_sizeY, 0.5 * wall2_sizeZ);
    G4LogicalVolume* logicwall2 =new G4LogicalVolume(solidwall2,Al_mat,"Alwall2");         //its name, его имя
    new G4PVPlacement(0,G4ThreeVector(Al_gorlX, Al_gorlY, Al_gorlZ), logicwall2, "Alwall2",logicWorld,false, 0,checkOverlaps);

    // Al перегородка 1 мм

    G4Box* solidwall3 =new G4Box("Alwall3",0.5 * wall2_sizeX, 0.5 * wall2_sizeY, 0.5 * wall2_sizeZ);
    G4LogicalVolume* logicwall3 =new G4LogicalVolume(solidwall3,Al_mat,"Alwall3");         //its name, его имя
    new G4PVPlacement(0,G4ThreeVector(-Al_gorlX, Al_gorlY, Al_gorlZ),logicwall3,"Alwall3",logicWorld,false, 0,checkOverlaps);

    

    //DSSD

    G4Box* solidDSSD = new G4Box("DSSD", 0.5 * DSSD_sizeX, 0.5 * DSSD_sizeY, 0.5 * DSSD_sizeZ); //its size, размеры
    G4LogicalVolume* logicDSSD = new G4LogicalVolume(solidDSSD, DSSD_mat, "DSSD");
    new G4PVPlacement(0, G4ThreeVector(DSSD_X, DSSD_Y, DSSD_Z), logicDSSD, "DSSD", logicWorld, false, 0, checkOverlaps);//000

    G4Box* solidDSSD_2 = new G4Box("DSSD_2", 0.5 * DSSD_sizeX, 0.5 * DSSD_sizeZ, 0.5 * DSSD_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDSSD_2 = new G4LogicalVolume(solidDSSD_2, DSSD_mat, "DSSD_2");
    new G4PVPlacement(0, G4ThreeVector(DSSD_X_2, DSSD_Y_2, DSSD_Z_2), logicDSSD_2, "DSSD_2", logicWorld, false, 0, checkOverlaps);
    
    G4Box* solidDSSD_3 = new G4Box("DSSD_3", 0.5 * DSSD_sizeX, 0.5 * DSSD_sizeZ, 0.5 * DSSD_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDSSD_3 = new G4LogicalVolume(solidDSSD_3, DSSD_mat, "DSSD_3");
    new G4PVPlacement(0, G4ThreeVector(DSSD_X_2, -DSSD_Y_2, DSSD_Z_2), logicDSSD_3, "DSSD_3", logicWorld, false, 0, checkOverlaps);

    G4Box* solidDSSD_4 = new G4Box("DSSD_4", 0.5 * DSSD_sizeZ, 0.5 * DSSD_sizeY, 0.5 * DSSD_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDSSD_4 = new G4LogicalVolume(solidDSSD_4, DSSD_mat, "DSSD_4");
    new G4PVPlacement(0, G4ThreeVector(DSSD_Y_2, DSSD_X_2, DSSD_Z_2), logicDSSD_4, "DSSD_4", logicWorld, false, 0, checkOverlaps);

    G4Box* solidDSSD_5 = new G4Box("DSSD_5", 0.5 * DSSD_sizeZ, 0.5 * DSSD_sizeY, 0.5 * DSSD_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDSSD_5 = new G4LogicalVolume(solidDSSD_5, DSSD_mat, "DSSD_5");
    new G4PVPlacement(0, G4ThreeVector(-DSSD_Y_2, DSSD_X_2, DSSD_Z_2), logicDSSD_5, "DSSD_5", logicWorld, false, 0, checkOverlaps);

    // Al стакан толщиной 1 мм

    G4Box* solidglass =new G4Box("Alglass",0.5 * glass_sizeXY, 0.5 * glass_sizeXY, 0.5 * glass_sizeZ);
    G4LogicalVolume* logicglass =new G4LogicalVolume(solidglass,Al_mat,"Alglass");         //its name, его имя
    new G4PVPlacement(0,G4ThreeVector(glass_X, glass_Y, glass_Z), logicglass,"Alglass",logicWorld,false,0,checkOverlaps);


   /* //Углеродное входное окно толщиной 0,6мм . 
    G4Box* solidwindow =new G4Box("window",0.5 * window_sizeXY, 0.5 * window_sizeXY, 0.5 * window_sizeZ);
    G4LogicalVolume* logicwindow =new G4LogicalVolume(solidwindow, C_mat,"window");
    new G4PVPlacement(0,G4ThreeVector(window_X, window_Y, window_Z),logicwindow,"window",logicWorld,false,0,checkOverlaps);*/

    /* //Тефлоновый кожух толщиной 1мм
     G4double tefl_sizeXY = 9 * cm, tefl_sizeZ = 0.1 * cm;
     G4Box* solidtefl =
         new G4Box("tefl",                    //its name, имя
             0.5 * tefl_sizeXY, 0.5 * tefl_sizeXY, 0.5 * tefl_sizeZ);
     G4LogicalVolume* logictefl =
         new G4LogicalVolume(solidtefl,            //its solid, объем
             C2F4,
             "tefl");         //its name, его имя
     new G4PVPlacement(0,                       //no rotation, так же без вращения
         G4ThreeVector(0., 0., 11.5 * mm),//
         logictefl,
         "tefl",
         logicWorld,
         false,
         0,
         checkOverlaps);*/
    
/// UP Y
    G4Box* solidDet_2 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDet_2 = new G4LogicalVolume(solidDet_2, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_2, Y_2, Z_2), logicDet_2, "Detector", logicWorld, false, 0, checkOverlaps);  
    //det NW
    G4Box* solidDetNW_2 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDetNW_2 = new G4LogicalVolume(solidDetNW_2, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_2, Y_2, Z_2), logicDetNW_2, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SW
    G4Box* solidDetSW_2 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDetSW_2 = new G4LogicalVolume(solidDetSW_2, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_2, Y_2, -Z_2), logicDetSW_2, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SE
    G4Box* solidDetSE_2 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDetSE_2 = new G4LogicalVolume(solidDetSE_2, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_2, Y_2, -Z_2), logicDetSE_2, "Detector", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall_2 = new G4Box("Alwall_2", 0.5 * wall_sizeX_2, 0.5 * wall_sizeY_2, 0.5 * wall_sizeZ_2);
    G4LogicalVolume* logicwall_2 = new G4LogicalVolume(solidwall_2, Al_mat, "Alwall_2");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(Al_verX_2, Al_verY_2, Al_verZ_2), logicwall_2, "Alwall_2", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall2_2 = new G4Box("Alwall2_2", 0.5 * wall2_sizeX_2, 0.5 * wall2_sizeY_2, 0.5 * wall2_sizeZ_2);
    G4LogicalVolume* logicwall2_2 = new G4LogicalVolume(solidwall2_2, Al_mat, "Alwall2_2");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(Al_gorlX_2, Al_gorlY_2, Al_gorlZ_2), logicwall2_2, "Alwall2_2", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall3_2 = new G4Box("Alwall3_2", 0.5 * wall2_sizeX_2, 0.5 * wall2_sizeY_2, 0.5 * wall2_sizeZ_2);
    G4LogicalVolume* logicwall3_2 = new G4LogicalVolume(solidwall3_2, Al_mat, "Alwall3");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(-Al_gorlX_2, Al_gorlY_2, Al_gorlZ_2), logicwall3_2, "Alwall3_2", logicWorld, false, 0, checkOverlaps);
    // Al стакан толщиной 1 мм
    G4Box* solidglass_2 = new G4Box("Alglass_2", 0.5 * glass_sizeX_2, 0.5 * glass_sizeY_2, 0.5 * glass_sizeZ_2);
    G4LogicalVolume* logicglass_2 = new G4LogicalVolume(solidglass_2, Al_mat, "Alglass_2");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(glass_X_2, glass_Y_2, glass_Z_2), logicglass_2, "Alglass_2", logicWorld, false, 0, checkOverlaps);
   /* //Углеродное входное окно толщиной 0,6мм . 
    G4Box* solidwindow_2 = new G4Box("window_2", 0.5 * window_sizeX_2, 0.5 * window_sizeY_2, 0.5 * window_sizeZ_2);
    G4LogicalVolume* logicwindow_2 = new G4LogicalVolume(solidwindow_2, C_mat, "window_2");
    new G4PVPlacement(0, G4ThreeVector(window_X_2, window_Y_2, window_Z_2), logicwindow_2, "window_2", logicWorld, false, 0, checkOverlaps);*/
   
    
    /// DOWN Y
    G4Box* solidDet_3 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDet_3 = new G4LogicalVolume(solidDet_3, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_2, -Y_2, Z_2), logicDet_3, "Detector", logicWorld, false, 0, checkOverlaps);
    //det NW
    G4Box* solidDetNW_3 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDetNW_3 = new G4LogicalVolume(solidDetNW_3, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_2, -Y_2, Z_2), logicDetNW_3, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SW
    G4Box* solidDetSW_3 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2);
    G4LogicalVolume* logicDetSW_3 = new G4LogicalVolume(solidDetSW_3, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_2, -Y_2, -Z_2), logicDetSW_3, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SE
    G4Box* solidDetSE_3 = new G4Box("Detector", 0.5 * det_sizeX_2, 0.5 * det_sizeY_2, 0.5 * det_sizeZ_2); //its size, размеры
    G4LogicalVolume* logicDetSE_3 = new G4LogicalVolume(solidDetSE_3, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_2, -Y_2, -Z_2), logicDetSE_3, "Detector", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall_3 = new G4Box("Alwall_3", 0.5 * wall_sizeX_2, 0.5 * wall_sizeY_2, 0.5 * wall_sizeZ_2);
    G4LogicalVolume* logicwall_3 = new G4LogicalVolume(solidwall_2, Al_mat, "Alwall_3");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(Al_verX_2, -Al_verY_2, Al_verZ_2), logicwall_3, "Alwall_3", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall2_3 = new G4Box("Alwall2_3", 0.5 * wall2_sizeX_2, 0.5 * wall2_sizeY_2, 0.5 * wall2_sizeZ_2);
    G4LogicalVolume* logicwall2_3 = new G4LogicalVolume(solidwall2_3, Al_mat, "Alwall2_3");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(Al_gorlX_2, -Al_gorlY_2, Al_gorlZ_2), logicwall2_3, "Alwall2_3", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall3_3 = new G4Box("Alwall3_3", 0.5 * wall2_sizeX_2, 0.5 * wall2_sizeY_2, 0.5 * wall2_sizeZ_2);
    G4LogicalVolume* logicwall3_3 = new G4LogicalVolume(solidwall3_3, Al_mat, "Alwall3");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(-Al_gorlX_2, -Al_gorlY_2, Al_gorlZ_2), logicwall3_3, "Alwall3_3", logicWorld, false, 0, checkOverlaps);
    // Al стакан толщиной 1 мм
    G4Box* solidglass_3 = new G4Box("Alglass_3", 0.5 * glass_sizeX_2, 0.5 * glass_sizeY_2, 0.5 * glass_sizeZ_2);
    G4LogicalVolume* logicglass_3 = new G4LogicalVolume(solidglass_3, Al_mat, "Alglass_3");         //its name, его имя
    new G4PVPlacement(0, G4ThreeVector(glass_X_2, -glass_Y_2, glass_Z_2), logicglass_2, "Alglass_3", logicWorld, false, 0, checkOverlaps);
    //Углеродное входное окно толщиной 0,6мм . 
    /*G4Box* solidwindow_3 = new G4Box("window_3", 0.5 * window_sizeX_2, 0.5 * window_sizeY_2, 0.5 * window_sizeZ_2);
    G4LogicalVolume* logicwindow_3 = new G4LogicalVolume(solidwindow_3, C_mat, "window_3");
    new G4PVPlacement(0, G4ThreeVector(window_X_2, -window_Y_2, window_Z_2), logicwindow_3, "window_3", logicWorld, false, 0, checkOverlaps);*/


    /// DOWN X
    G4Box* solidDet_4 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDet_4 = new G4LogicalVolume(solidDet_4, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_4, -Y_4, Z_4), logicDet_4, "Detector", logicWorld, false, 0, checkOverlaps);
    //det NW
    G4Box* solidDetNW_4 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetNW_4 = new G4LogicalVolume(solidDetNW_4, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_4, Y_4, Z_4), logicDetNW_4, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SW
    G4Box* solidDetSW_4 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetSW_4 = new G4LogicalVolume(solidDetSW_4, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_4, Y_4, -Z_4), logicDetSW_4, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SE
    G4Box* solidDetSE_4 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetSE_4 = new G4LogicalVolume(solidDetSE_4, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(-X_4, -Y_4, -Z_4), logicDetSE_4, "Detector", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall_4 = new G4Box("Alwall_4", 0.5 * wall_sizeX_4, 0.5 * wall_sizeY_4, 0.5 * wall_sizeZ_4);
    G4LogicalVolume* logicwall_4 = new G4LogicalVolume(solidwall_4, Al_mat, "Alwall_4");  
    new G4PVPlacement(0, G4ThreeVector(-Al_verX_4, Al_verY_4, Al_verZ_4), logicwall_4, "Alwall_4", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall2_4 = new G4Box("Alwall2_4", 0.5 * wall2_sizeX_4, 0.5 * wall2_sizeY_4, 0.5 * wall2_sizeZ_4);
    G4LogicalVolume* logicwall2_4 = new G4LogicalVolume(solidwall2_4, Al_mat, "Alwall2_4");  
    new G4PVPlacement(0, G4ThreeVector(-Al_gorlX_4, Al_gorlY_4, Al_gorlZ_4), logicwall2_4, "Alwall2_4", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall3_4 = new G4Box("Alwall3_4", 0.5 * wall2_sizeX_4, 0.5 * wall2_sizeY_4, 0.5 * wall2_sizeZ_4);
    G4LogicalVolume* logicwall3_4 = new G4LogicalVolume(solidwall3_4, Al_mat, "Alwall4"); 
    new G4PVPlacement(0, G4ThreeVector(-Al_gorlX_4, -Al_gorlY_4, Al_gorlZ_4), logicwall3_4, "Alwall3_4", logicWorld, false, 0, checkOverlaps);
    // Al стакан толщиной 1 мм
    G4Box* solidglass_4 = new G4Box("Alglass_4", 0.5 * glass_sizeX_4, 0.5 * glass_sizeY_4, 0.5 * glass_sizeZ_4);
    G4LogicalVolume* logicglass_4 = new G4LogicalVolume(solidglass_4, Al_mat, "Alglass_4");     
    new G4PVPlacement(0, G4ThreeVector(-glass_X_4, glass_Y_4, glass_Z_4), logicglass_4, "Alglass_4", logicWorld, false, 0, checkOverlaps);
    //Углеродное входное окно толщиной 0,6мм . 
    /*G4Box* solidwindow_4 = new G4Box("window_4", 0.5 * window_sizeX_4, 0.5 * window_sizeY_4, 0.5 * window_sizeZ_4);
    G4LogicalVolume* logicwindow_4 = new G4LogicalVolume(solidwindow_4, C_mat, "window_4");
    new G4PVPlacement(0, G4ThreeVector(-window_X_4, window_Y_4, window_Z_4), logicwindow_4, "window_4", logicWorld, false, 0, checkOverlaps);*/

    /// UP XXXXXX

    G4Box* solidDet_5 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDet_5 = new G4LogicalVolume(solidDet_5, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_4, -Y_4, Z_4), logicDet_5, "Detector", logicWorld, false, 0, checkOverlaps);
    //det NW
    G4Box* solidDetNW_5 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetNW_5 = new G4LogicalVolume(solidDetNW_5, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_4, Y_4, Z_4), logicDetNW_5, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SW
    G4Box* solidDetSW_5 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetSW_5 = new G4LogicalVolume(solidDetSW_5, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_4, Y_4, -Z_4), logicDetSW_5, "Detector", logicWorld, false, 0, checkOverlaps);
    //DET SE
    G4Box* solidDetSE_5 = new G4Box("Detector", 0.5 * det_sizeX_4, 0.5 * det_sizeY_4, 0.5 * det_sizeZ_4);
    G4LogicalVolume* logicDetSE_5 = new G4LogicalVolume(solidDetSE_5, det_mat, "Detector");
    new G4PVPlacement(0, G4ThreeVector(X_4, -Y_4, -Z_4), logicDetSE_5, "Detector", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall_5 = new G4Box("Alwall_5", 0.5 * wall_sizeX_4, 0.5 * wall_sizeY_4, 0.5 * wall_sizeZ_4);
    G4LogicalVolume* logicwall_5 = new G4LogicalVolume(solidwall_5, Al_mat, "Alwall_5");
    new G4PVPlacement(0, G4ThreeVector(Al_verX_4, Al_verY_4, Al_verZ_4), logicwall_5, "Alwall_5", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall2_5 = new G4Box("Alwall2_5", 0.5 * wall2_sizeX_4, 0.5 * wall2_sizeY_4, 0.5 * wall2_sizeZ_4);
    G4LogicalVolume* logicwall2_5 = new G4LogicalVolume(solidwall2_5, Al_mat, "Alwall2_5");
    new G4PVPlacement(0, G4ThreeVector(Al_gorlX_4, Al_gorlY_4, Al_gorlZ_4), logicwall2_5, "Alwall2_5", logicWorld, false, 0, checkOverlaps);
    // Al перегородка 1 мм
    G4Box* solidwall3_5 = new G4Box("Alwall3_5", 0.5 * wall2_sizeX_4, 0.5 * wall2_sizeY_4, 0.5 * wall2_sizeZ_4);
    G4LogicalVolume* logicwall3_5 = new G4LogicalVolume(solidwall3_5, Al_mat, "Alwall5");
    new G4PVPlacement(0, G4ThreeVector(Al_gorlX_4, -Al_gorlY_4, Al_gorlZ_4), logicwall3_5, "Alwall3_5", logicWorld, false, 0, checkOverlaps);
    // Al стакан толщиной 1 мм
    G4Box* solidglass_5 = new G4Box("Alglass_5", 0.5 * glass_sizeX_4, 0.5 * glass_sizeY_4, 0.5 * glass_sizeZ_4);
    G4LogicalVolume* logicglass_5 = new G4LogicalVolume(solidglass_5, Al_mat, "Alglass_5");
    new G4PVPlacement(0, G4ThreeVector(glass_X_4, glass_Y_4, glass_Z_4), logicglass_5, "Alglass_5", logicWorld, false, 0, checkOverlaps);
    //Углеродное входное окно толщиной 0,6мм . 
    /*G4Box* solidwindow_5 = new G4Box("window_5", 0.5 * window_sizeX_4, 0.5 * window_sizeY_4, 0.5 * window_sizeZ_4);
    G4LogicalVolume* logicwindow_5 = new G4LogicalVolume(solidwindow_5, C_mat, "window_5");
    new G4PVPlacement(0, G4ThreeVector(window_X_4, window_Y_4, window_Z_4), logicwindow_5, "window_5", logicWorld, false, 0, checkOverlaps);*/
    return physWorld;
}

void ExG4DetectorConstruction01::ConstructSDandField()
{
    // Объявление чувствительной области детектора, в которой можно получить подробную
    // информацию о состоянии и движении частицы, не работает в многопоточной версии
    // Назовем чувствительную область DetectorSD
    G4String trackerChamberSDname1 = "DetectorSD1";
    // Создаем экземпляр чувствительной области
    ExG4DetectorSD* aTrackerSD1 = new ExG4DetectorSD(trackerChamberSDname1);
    // Передаем указатель менеджеру
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD1);
    // Добавляем чувствительный объем ко всем логическим областям с
    // именем Detector
    SetSensitiveDetector("Detector", aTrackerSD1, true);

   /* G4String trackerChamberSDname2 = "DetectorSD2";
    ExG4DetectorSD* aTrackerSD2 = new ExG4DetectorSD(trackerChamberSDname2);
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD2);
    SetSensitiveDetector("Detector2", aTrackerSD2, true);

    G4String trackerChamberSDname3 = "DetectorSD3";
    ExG4DetectorSD* aTrackerSD3 = new ExG4DetectorSD(trackerChamberSDname3);
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD3);
    SetSensitiveDetector("Detector3", aTrackerSD3, true);

    G4String trackerChamberSDname4 = "DetectorSD4";
    ExG4DetectorSD* aTrackerSD4 = new ExG4DetectorSD(trackerChamberSDname4);
    G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD4);
    SetSensitiveDetector("Detector4", aTrackerSD4, true);*/

}
