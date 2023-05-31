#ifndef ExG4PhysicsList_h
#define ExG4PhysicsList_h 1
#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4VUserPhysicsList.hh"
/*class ExG4PhysicsListMessenger;
class G4VPhysicsConstructor;*/

class ExG4PhysicsList : public G4VUserPhysicsList
{

public:
    ExG4PhysicsList();
    ~ExG4PhysicsList();
    void SetCutForGamma(G4double);
    void SetCutForElectron(G4double);
    void SetCutForPositron(G4double);
protected:
    // Construct particle and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();

    virtual void SetCuts();

private:
    

    G4double cutForGamma;
    G4double cutForElectron;
    G4double cutForPositron;

protected:
    // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

