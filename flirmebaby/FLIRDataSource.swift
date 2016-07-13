import Foundation

enum Palette: String {
    case Arctic = "Arctic"
    case Hottest = "Hottest"
    case Gray = "Gray"
    case Iron = "Iron"
    case Contrast = "Contrast"
    case Rainbow = "Rainbow"
    case Coldest = "Coldest"
}

enum FLIRImageOptions {
    case BlendedMSXRGBA8888
    case ThermalRGBA8888
    case LinearFlux14Bit
    case RadiometricKelvinx100
    case VisualJPEG
    case VisualYCbCr
}

typealias VoidClosure = () -> (Void)
typealias ImageReceptionClosure = (UIImage, CGSize) -> Void

protocol FLIRDataSourceProtocol {
    var palette: Palette { get set }
    var didConnectClosure: VoidClosure { get set }
    var didReceiveImageClosure: ImageReceptionClosure? { get set }
}

class FLIRDataSource: NSObject, FLIRDataSourceProtocol, FLIROneSDKImageReceiverDelegate, FLIROneSDKStreamManagerDelegate {

    var palette: Palette = .Iron {
        //Did connect closure is a good place to set this.
        didSet {
            if let FLIROneSDKPalettes = (FLIROneSDKPalette.palettes() as? [String: FLIROneSDKPalette]), FLIROneSDKPalette = FLIROneSDKPalettes[palette.rawValue] {
                FLIROneSDKStreamManager.sharedInstance().palette? = FLIROneSDKPalette
            }
        }
    }

    var didConnectClosure: VoidClosure = {}
    var didReceiveImageClosure: ImageReceptionClosure?

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
        FLIROneSDKSimulation.sharedInstance().connectWithFrameBundleName("sampleframes_hq", withBatteryChargePercentage: 42)
    }

    func FLIROneSDKDidConnect() {
        didConnectClosure()
    }


    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveBlendedMSXRGBA8888Image msxImage: NSData!, imageSize size: CGSize) {
        didReceiveImageClosure?(UIImage(), size)
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveRadiometricData radiometricData: NSData!, imageSize size: CGSize) {
    }
}
