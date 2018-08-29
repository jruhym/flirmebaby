import Foundation

enum Palette: String {
    case undefined = ""
    case arctic = "Arctic"
    case hottest = "Hottest"
    case gray = "Gray"
    case iron = "Iron"
    case contrast = "Contrast"
    case rainbow = "Rainbow"
    case coldest = "Coldest"
}

enum FLIRImageOptions: UInt64 {
    case linearFlux14Bit = 0x1
    case thermalRGBA8888 = 0x2
    case blendedMSXRGBA8888 = 0x4
    case visualJPEG = 0x8
    case visualYCbCr = 0x10
    case radiometricKelvinx100 = 0x20
}

typealias VoidClosure = () -> Void
typealias ImageReceptionClosure = (UIImage, CGSize) -> Void
typealias DataReceptionClosure = (Data, CGSize) -> Void

protocol FLIRDataSourceProtocol {
    var palette: Palette { get set }
    var imageOptions: [FLIRImageOptions]? { get set }
    var didConnectClosure: VoidClosure? { get set }
    var didDisconnectClosure: VoidClosure? { get set }
    var didReceiveImageClosure: ImageReceptionClosure? { get set }
    var didReceiveDataClosure: DataReceptionClosure? { get set }
    var isDemoShown: Bool { get set }
    func showDemo()
}

class FLIRDataSource: NSObject, FLIRDataSourceProtocol {

    lazy var FLIROneSDKPalettes: [String: FLIROneSDKPalette]? = FLIROneSDKPalette.palettes() as? [String: FLIROneSDKPalette]
    var palette: Palette = .undefined {
        // Did-connect closure is a good place to initialize this.
        didSet {
            if palette != oldValue, let FLIROnePalette = FLIROneSDKPalettes?[palette.rawValue] {
                FLIROneSDKStreamManager.sharedInstance().palette? = FLIROnePalette
            }
        }
    }

    var didConnectClosure: VoidClosure?
    var didDisconnectClosure: VoidClosure?
    var didReceiveImageClosure: ImageReceptionClosure?
    var didReceiveDataClosure: DataReceptionClosure?
    var imageOptions: [FLIRImageOptions]? {
        didSet {
            var sdkImageOptionsRawValue: UInt64 = 0
            for imageOption in imageOptions ?? [] {
                sdkImageOptionsRawValue += imageOption.rawValue
            }
            if let sdkImageOptions = FLIROneSDKImageOptions(rawValue: sdkImageOptionsRawValue), sdkImageOptionsRawValue > 0 {
                FLIROneSDKStreamManager.sharedInstance().imageOptions = sdkImageOptions
            }
        }
    }
    var isDemoShown = false
    fileprivate var isDemoRequested = false

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
        NotificationCenter.default.addObserver(self, selector: #selector(requestDemoIfNeeded), name: .UIApplicationWillResignActive, object: nil)
    }

    @objc fileprivate func requestDemoIfNeeded() {
        isDemoRequested = isDemoShown
    }

    deinit {
        FLIROneSDKStreamManager.sharedInstance().removeDelegate(self)
        NotificationCenter.default.removeObserver(self)
    }

    func showDemo() {
        guard !isDemoShown else {
            return
        }
        if FLIROneSDKSimulation.sharedInstance().isAvailable() {
            FLIROneSDKSimulation.sharedInstance().connect(withFrameBundleName: "sampleframes_hq", withBatteryChargePercentage: 42)
            isDemoRequested = true
        }
    }
}

extension FLIRDataSource: FLIROneSDKImageReceiverDelegate, FLIROneSDKStreamManagerDelegate {

    func flirOneSDKDelegateManager(_ delegateManager: FLIROneSDKDelegateManager!, didReceiveRadiometricData radiometricData: Data!, imageSize size: CGSize, sequenceNumber: Int) {
        didReceiveDataClosure?(radiometricData, size)
    }

    func flirOneSDKDelegateManager(_ delegateManager: FLIROneSDKDelegateManager!, didReceiveBlendedMSXRGBA8888Image msxImage: Data!, imageSize size: CGSize, sequenceNumber: Int) {
        if let image = FLIROneSDKUIImage(format: FLIROneSDKImageOptions.blendedMSXRGBA8888Image, andData: msxImage, andSize: size) {
            didReceiveImageClosure?(image, size)
        }
    }

    func flirOneSDKDidConnect() {
        if isDemoRequested {
            isDemoShown = true
            isDemoRequested = false
        }
        didConnectClosure?()
    }

    func flirOneSDKDidDisconnect() {
        isDemoShown = false
        didDisconnectClosure?()
    }
}
