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
    case LinearFlux14Bit = 0x1
    case ThermalRGBA8888 = 0x2
    case BlendedMSXRGBA8888 = 0x4
    case VisualJPEG = 0x8
    case VisualYCbCr = 0x10
    case RadiometricKelvinx100 = 0x20
}

typealias VoidClosure = () -> (Void)
typealias ImageReceptionClosure = (UIImage, CGSize) -> Void
typealias DataReceptionClosure = (NSData, CGSize) -> Void

protocol FLIRDataSourceProtocol {
    var palette: Palette { get set }
    var imageOptions: [FLIRImageOptions]? { get set }
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
    var imageOptions: [FLIRImageOptions]? {
        didSet {
            var sdkImageOptionsRawValue: UInt64 = 0
            for imageOption in imageOptions ?? [] {
                sdkImageOptionsRawValue += imageOption.rawValue
            }
            if let sdkImageOptions = FLIROneSDKImageOptions(rawValue: sdkImageOptionsRawValue) where sdkImageOptionsRawValue > 0 {
                FLIROneSDKStreamManager.sharedInstance().imageOptions = sdkImageOptions
                FLIROneSDKSimulation.sharedInstance().connectWithFrameBundleName("sampleframes_hq", withBatteryChargePercentage: 42)
            }
        }
    }

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
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
