#include "DetectorConstruction.hh"

#include "G4RunManager.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4SubtractionSolid.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "HyperParameters.hh"

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4NistManager* nist = G4NistManager::Instance();
  G4double world_sizeX = 50*cm, world_sizeY = 30*cm, world_sizeZ = 30*cm;
  G4bool checkOverlaps = true; 
  G4Material* world_material = nist->FindOrBuildMaterial("G4_Galactic");

  G4Box* solidWorld = new G4Box("World", world_sizeX, world_sizeY, world_sizeZ);

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,              // its solid
                        world_material,          // its material
                        "World");                // its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);         //overlaps checking
  
  G4double wide = 1*mm;
  G4Material* plast_mat = nist->FindOrBuildMaterial("G4_Cu");

  G4Box* plast = new G4Box("Plast", wide, 10*cm, 10*cm);
  G4LogicalVolume* logicPlast = new G4LogicalVolume(plast, plast_mat, "Plast");
  G4VPhysicalVolume* physPlast = new G4PVPlacement(0, G4ThreeVector(), logicPlast, "Plast", logicWorld, false, 0, checkOverlaps);
  
  return physWorld;

}