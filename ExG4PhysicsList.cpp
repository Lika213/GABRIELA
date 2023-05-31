#include "ExG4PhysicsList.hh"
#include "G4RunManager.hh"
#include "globals.hh"
#include "G4ProcessManager.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4EmLivermorePhysics.hh"
#include "G4ParticleDefinition.hh"
// *** Processes and models
// gamma
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"
// e-
#include "G4eMultipleScattering.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4Generator2BS.hh"

// e+
#include "G4eplusAnnihilation.hh"
#include "G4RayleighScattering.hh"
#include "G4LivermoreRayleighModel.hh"
#include "globals.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
// Bosons
#include "G4ChargedGeantino.hh"
#include "G4Geantino.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"
//#include "G4EmProcessOptions.hh"
#include "G4UAtomicDeexcitation.hh"
#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"
#include "G4PhysicsConstructorFactory.hh"

//#include "G4UrbanMscModel95.hh"
#include "G4WentzelVIModel.hh"
#include "G4GoudsmitSaundersonMscModel.hh"
#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
// e-

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4UniversalFluctuation.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4KleinNishinaModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
// e+

#include "G4eplusAnnihilation.hh"

// mu

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

// hadrons, ions

#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"
G4_DECLARE_PHYSCONSTR_FACTORY(G4EmLivermorePhysics);
ExG4PhysicsList::ExG4PhysicsList() : G4VUserPhysicsList()
{
    G4LossTableManager::Instance();
    defaultCutValue = 1. * mm;
    cutForGamma = defaultCutValue;
    cutForElectron = defaultCutValue;
    cutForPositron = defaultCutValue;
    //messenger = new PhysicsListMessenger(this);
    SetVerboseLevel(0);


}

ExG4PhysicsList::~ExG4PhysicsList()
{
    /*//delete messenger;
    delete emPhysicsList; */
}

void ExG4PhysicsList::ConstructParticle()
{

    // gamma
    G4Gamma::Gamma();

    // leptons
    G4Electron::Electron();
    G4Positron::Positron();
    G4MuonPlus::MuonPlus();
    G4MuonMinus::MuonMinus();

    // mesons
    G4PionPlus::PionPlusDefinition();
    G4PionMinus::PionMinusDefinition();
    G4KaonPlus::KaonPlusDefinition();
    G4KaonMinus::KaonMinusDefinition();

    // barions
    G4Proton::Proton();
    G4AntiProton::AntiProton();

    // ions
    G4Deuteron::Deuteron();
    G4Triton::Triton();
    G4He3::He3();
    G4Alpha::Alpha();
    G4GenericIon::GenericIonDefinition();
}
/*void ExG4PhysicsList::ConstructBosons()
{
    G4Gamma::GammaDefinition();
}*/
void ExG4PhysicsList::ConstructProcess()
{
    // transportation
    AddTransportation();
    // electromagnetic physics list
    ConstructEM();
}

#include "G4PolarizedPhotoElectricModel.hh"
#include "G4LowEPComptonModel.hh"
#include "G4BetheHeitler5DModel.hh"
#include "G4JAEAElasticScatteringModel.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4PhysicsList::ConstructEM()
{
    G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

    auto particleIterator = GetParticleIterator();
    particleIterator->reset();
    G4double highEnergyLimit = 100 * MeV;
    while ((*particleIterator)()) {
        G4ParticleDefinition* particle = particleIterator->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        G4double highEnergyLimit = 1 * GeV;
        G4double LivermoreHighEnergyLimit = GeV;

        if (particleName == "gamma") {
            // gamma         
            // Compton scattering
            G4ComptonScattering* cs = new G4ComptonScattering;
            cs->SetEmModel(new G4LowEPComptonModel(), 1);
            ph->RegisterProcess(cs, particle);

            // Photoelectric
            G4PhotoElectricEffect* pe = new G4PhotoElectricEffect();
            G4VEmModel* thePEModel = new G4PolarizedPhotoElectricModel();
            thePEModel->SetHighEnergyLimit(10 * GeV);
            pe->SetEmModel(thePEModel, 1);
            ph->RegisterProcess(pe, particle);

            // Gamma conversion
            G4GammaConversion* gc = new G4GammaConversion();
            G4VEmModel* theGCModel = new G4BetheHeitler5DModel();
            theGCModel->SetHighEnergyLimit(1 * GeV);
            gc->SetEmModel(theGCModel, 1);
            ph->RegisterProcess(gc, particle);

            // Rayleigh scattering
            G4RayleighScattering* rs = new G4RayleighScattering;
            rs->SetEmModel(new G4JAEAElasticScatteringModel(), 1);
            ph->RegisterProcess(rs, particle);
            // ph->RegisterProcess(new G4RayleighScattering(), particle);
           // THERE
           /*G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
             G4LivermorePhotoElectricModel*
                 photModel = new G4LivermorePhotoElectricModel();
             photModel->SetHighEnergyLimit(highEnergyLimit);
             phot->AddEmModel(0, photModel);
             ///list->RegisterProcess(phot, particle);
             pmanager->AddDiscreteProcess(phot);

             G4ComptonScattering* compt = new G4ComptonScattering();
             G4LivermoreComptonModel*
                 comptModel = new G4LivermoreComptonModel();
             comptModel->SetHighEnergyLimit(highEnergyLimit);
             compt->AddEmModel(0, comptModel);
             pmanager->AddDiscreteProcess(compt);

             G4GammaConversion* conv = new G4GammaConversion();
             G4LivermoreGammaConversionModel*
                 convModel = new G4LivermoreGammaConversionModel();
             convModel->SetHighEnergyLimit(highEnergyLimit);
             conv->AddEmModel(0, convModel);
             pmanager->AddDiscreteProcess(conv);

            G4RayleighScattering* rayl = new G4RayleighScattering();
             G4LivermoreRayleighModel*
                 raylModel = new G4LivermoreRayleighModel();
             raylModel->SetHighEnergyLimit(highEnergyLimit);
             rayl->AddEmModel(0, raylModel);
             pmanager->AddDiscreteProcess(rayl);
             */ //THERE
        }

        else if (particleName == "e-") {
            //electron

            G4eIonisation* eIoni = new G4eIonisation();
            G4LivermoreIonisationModel*
                eIoniModel = new G4LivermoreIonisationModel();
            eIoniModel->SetHighEnergyLimit(highEnergyLimit);
            eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation());
            pmanager->AddProcess(eIoni, -1, -1, 1);

            G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
            G4LivermoreBremsstrahlungModel*
                eBremModel = new G4LivermoreBremsstrahlungModel();
            eBremModel->SetHighEnergyLimit(highEnergyLimit);
            eBrem->AddEmModel(0, eBremModel);
            pmanager->AddProcess(eBrem, -1, -1, 2);

        }/*
        else if (particleName == "e+") {
            //positron
            pmanager->AddProcess(new G4eIonisation, -1, -1, 1);
            pmanager->AddProcess(new G4eBremsstrahlung, -1, -1, 2);
            pmanager->AddProcess(new G4eplusAnnihilation, 0, -1, 3);

        }*/
        /*else if (particleName == "mu+" ||
            particleName == "mu-") {
            //muon
            pmanager->AddProcess(new G4MuIonisation, -1, -1, 1);
            pmanager->AddProcess(new G4MuBremsstrahlung, -1, -1, 2);
            pmanager->AddProcess(new G4MuPairProduction, -1, -1, 3);

        }
        else if (particleName == "alpha" || particleName == "GenericIon") {
            pmanager->AddProcess(new G4ionIonisation, -1, -1, 1);

        }
        else if ((!particle->IsShortLived()) &&
            (particle->GetPDGCharge() != 0.0) &&
            (particle->GetParticleName() != "chargedgeantino")) {
            //all others charged particles except geantino
            pmanager->AddProcess(new G4hIonisation, -1, -1, 1);
        }*/
        /*
            if (particleName == "gamma") {

                // Photoelectric effect - define low-energy model
                G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
                G4LivermorePhotoElectricModel* theLivermorePhotoElectricModel = new G4LivermorePhotoElectricModel();
                thePhotoElectricEffect->SetEmModel(theLivermorePhotoElectricModel);
                ph->RegisterProcess(thePhotoElectricEffect, particle);*/

                /*G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
                G4LivermorePhotoElectricModel* theLivermorePhotoElectricModel = new G4LivermorePhotoElectricModel();
                theLivermorePhotoElectricModel->SetHighEnergyLimit(highEnergyLimit);
                thePhotoElectricEffect->AddEmModel(0, theLivermorePhotoElectricModel);
                ph->RegisterProcess(thePhotoElectricEffect, particle);*/

                ///list->RegisterProcess(phot, particle);


                /*// Compton scattering - define low-energy model
                G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
                G4LivermoreComptonModel* theLivermoreComptonModel = new G4LivermoreComptonModel();
                theLivermoreComptonModel->SetHighEnergyLimit(LivermoreHighEnergyLimit);
                theComptonScattering->SetEmModel(theLivermoreComptonModel, 1);
                ph->RegisterProcess(theComptonScattering, particle);*/

                /* G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
            G4LivermoreComptonModel*theLivermoreComptonModel = new G4LivermoreComptonModel();
            theLivermoreComptonModel->SetHighEnergyLimit(highEnergyLimit);
            theComptonScattering->AddEmModel(0, theLivermoreComptonModel);
            ph->RegisterProcess(theComptonScattering, particle);*/

            /* // gamma conversion - define low-energy model
             G4GammaConversion* theGammaConversion = new G4GammaConversion();
             G4VEmModel* theLivermoreGammaConversionModel = new G4LivermoreGammaConversionModel();
             theGammaConversion->AddEmModel(0,theLivermoreGammaConversionModel);
             ph->RegisterProcess(theGammaConversion, particle);*/

             /* // default Rayleigh scattering is Livermore
              G4RayleighScattering* theRayleigh = new G4RayleighScattering();
              ph->RegisterProcess(theRayleigh, particle
              */
              /*G4RayleighScattering* theRayleigh = new G4RayleighScattering();
             G4LivermoreRayleighModel*raylModel = new G4LivermoreRayleighModel();
             raylModel->SetHighEnergyLimit(highEnergyLimit);
             theRayleigh->AddEmModel(0, raylModel);

             ph->RegisterProcess(theRayleigh, particle); }*/

             /*else if (particleName == "e-") {
                 // multiple scattering
                 G4eMultipleScattering* msc = new G4eMultipleScattering;
                 msc->SetStepLimitType(fUseDistanceToBoundary);
                 //G4UrbanMscModel95* msc1 = new G4UrbanMscModel95();
                 G4WentzelVIModel* msc2 = new G4WentzelVIModel();
                 //msc1->SetHighEnergyLimit(highEnergyLimit);
                 msc2->SetLowEnergyLimit(highEnergyLimit);
                 //msc->AddEmModel(0, msc1);
                 msc->AddEmModel(0, msc2);

                 G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
                 G4CoulombScattering* ss = new G4CoulombScattering();
                 ss->SetEmModel(ssm, 1);
                 ss->SetMinKinEnergy(highEnergyLimit);
                 //sm->SetLowEnergyLimit(highEnergyLimit);
                 ssm->SetActivationLowEnergyLimit(highEnergyLimit);
                 ph->RegisterProcess(msc, particle);
                 ph->RegisterProcess(ss, particle);

                 // Ionisation - Livermore should be used only for low energies
                 G4eIonisation* eIoni = new G4eIonisation();
                 G4LivermoreIonisationModel* theIoniLivermore = new
                     G4LivermoreIonisationModel();
                 theIoniLivermore->SetHighEnergyLimit(0.1 * MeV);
                 eIoni->AddEmModel(0, theIoniLivermore, new G4UniversalFluctuation());
                 eIoni->SetStepFunction(0.2, 100 * um); //
                 ph->RegisterProcess(eIoni, particle);

                 // Bremsstrahlung
                 G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
                 G4VEmModel* theBremLivermore = new G4LivermoreBremsstrahlungModel();
                 theBremLivermore->SetHighEnergyLimit(1 * GeV);
                 //theBremLivermore->SetAngularDistribution(new G4Generator2BS());
                 eBrem->SetEmModel(theBremLivermore, 1);

                 ph->RegisterProcess(eBrem, particle);
             }*/
             /*else if (particleName == "e+") {
                 // Identical to G4EmStandardPhysics_option3
                     // multiple scattering
                 G4eMultipleScattering* msc = new G4eMultipleScattering;
                 msc->SetStepLimitType(fUseDistanceToBoundary);
                 //G4UrbanMscModel95* msc1 = new G4UrbanMscModel95();
                 G4WentzelVIModel* msc2 = new G4WentzelVIModel();
                 //msc1->SetHighEnergyLimit(highEnergyLimit);
                 msc2->SetLowEnergyLimit(highEnergyLimit);
                 //msc->AddEmModel(0, msc1);
                 msc->AddEmModel(0, msc2);
                 G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
                 G4CoulombScattering* ss = new G4CoulombScattering();
                 ss->SetEmModel(ssm, 1);
                 ss->SetMinKinEnergy(highEnergyLimit);
                 ssm->SetLowEnergyLimit(highEnergyLimit);
                 ssm->SetActivationLowEnergyLimit(highEnergyLimit);

                 G4eIonisation* eIoni = new G4eIonisation();
                 eIoni->SetStepFunction(0.2, 100 * um);

                 ph->RegisterProcess(msc, particle);
                 ph->RegisterProcess(eIoni, particle);
                 ph->RegisterProcess(new G4eBremsstrahlung(), particle);
                 ph->RegisterProcess(new G4eplusAnnihilation(), particle);
                 ph->RegisterProcess(ss, particle);
             }*/

    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExG4PhysicsList::SetCuts()
{
    if (verboseLevel > 0) {
        G4cout << "PhysicsList::SetCuts:";
        G4cout << "CutLength : " << defaultCutValue / mm << " (mm)" << G4endl;
    }

    // set cut values for gamma at first and for e- second and next for e+,
    // because some processes for e+/e- need cut values for gamma 
    SetCutValue(defaultCutValue, "gamma");
    SetCutValue(defaultCutValue, "e-");
    SetCutValue(defaultCutValue, "e+");

    if (verboseLevel > 0) DumpCutValuesTable();
}

/////////////////////////////////////////////////////////////////////////////
void ExG4PhysicsList::SetCutForGamma(G4double cut)
{
    cutForGamma = cut;
    SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

/////////////////////////////////////////////////////////////////////////////
void ExG4PhysicsList::SetCutForElectron(G4double cut)
{
    cutForElectron = cut;
    SetParticleCuts(cutForElectron, G4Electron::Electron());
}

/////////////////////////////////////////////////////////////////////////////
void ExG4PhysicsList::SetCutForPositron(G4double cut)
{
    cutForPositron = cut;
    SetParticleCuts(cutForPositron, G4Positron::Positron());
}
