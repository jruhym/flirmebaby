import Foundation

enum Palettes: String {
    case Arctic = "Arctic"
    case Hottest = "Hottest"
    case Gray = "Gray"
    case Iron = "Iron"
    case Contrast = "Contrast"
    case Rainbow = "Rainbow"
    case Coldest = "Coldest"
}

typealias VoidClosure = () -> (Void)

protocol FLIRDataSourceProtocol {
    var palette: Palettes { get set }
    var didConnectClosure: VoidClosure { get set }
}

class FLIRDataSource: NSObject, FLIRDataSourceProtocol, FLIROneSDKImageReceiverDelegate, FLIROneSDKStreamManagerDelegate {

    var palette: Palettes = .Iron {
        didSet {
            if let FLIROneSDKPalettes = (FLIROneSDKPalette.palettes() as? [String: FLIROneSDKPalette]), FLIROneSDKPalette = FLIROneSDKPalettes[palette.rawValue] {
                FLIROneSDKStreamManager.sharedInstance().palette? = FLIROneSDKPalette
            }
        }
    }

    var didConnectClosure: VoidClosure = {}

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
        FLIROneSDKSimulation.sharedInstance().connectWithFrameBundleName("sampleframes_hq", withBatteryChargePercentage: 42)
    }

    func FLIROneSDKDidConnect() {
        didConnectClosure()
    }


    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveBlendedMSXRGBA8888Image msxImage: NSData!, imageSize size: CGSize) {
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveRadiometricData radiometricData: NSData!, imageSize size: CGSize) {
    }
}
