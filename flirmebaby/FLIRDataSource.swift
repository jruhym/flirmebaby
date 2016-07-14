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

enum FLIRImageOptions: UInt64 {
    case BlendedMSXRGBA8888 = 0x1
    case ThermalRGBA8888 = 0x2
    case LinearFlux14Bit = 0x4
    case RadiometricKelvinx100 = 0x8
    case VisualJPEG = 0x10
    case VisualYCbCr = 0x20
}

typealias VoidClosure = () -> (Void)
typealias ImageReceptionClosure = (UIImage, CGSize) -> Void
typealias DataReceptionClosure = (NSData, CGSize) -> Void

protocol FLIRDataSourceProtocol {
    var palette: Palette { get set }
    var imageOptions: FLIRImageOptions? { get set }
    var didConnectClosure: VoidClosure? { get set }
    var didReceiveImageClosure: ImageReceptionClosure? { get set }
    var didReceiveDataClosure: DataReceptionClosure? { get set }
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

    var didConnectClosure: VoidClosure?
    var didReceiveImageClosure: ImageReceptionClosure?
    var didReceiveDataClosure: DataReceptionClosure?
    var imageOptions: FLIRImageOptions? {
        didSet {
            if let imageOptions = imageOptions, sdkImageOptions = FLIROneSDKImageOptions(rawValue: imageOptions.rawValue) {
                FLIROneSDKStreamManager.sharedInstance().imageOptions = sdkImageOptions
            }
        }
    }

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
        FLIROneSDKSimulation.sharedInstance().connectWithFrameBundleName("sampleframes_hq", withBatteryChargePercentage: 42)
    }

    func FLIROneSDKDidConnect() {
        didConnectClosure?()
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveBlendedMSXRGBA8888Image msxImage: NSData!, imageSize size: CGSize) {
        let image = FLIROneSDKUIImage(format: FLIROneSDKImageOptions.BlendedMSXRGBA8888Image, andData: msxImage, andSize: size)
        didReceiveImageClosure?(image, size)
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveRadiometricData radiometricData: NSData!, imageSize size: CGSize) {
        didReceiveDataClosure?(radiometricData, size)
    }
}
