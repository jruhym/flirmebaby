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

protocol FLIRDataSourceProtocol {
//    func FLIRDidConnect(item1, item2) in return item1 < item2)
}

class FLIRDataSource: NSObject, FLIROneSDKImageReceiverDelegate, FLIROneSDKStreamManagerDelegate {

    override init() {
        super.init()
        FLIROneSDKStreamManager.sharedInstance().addDelegate(self)
        FLIROneSDKSimulation.sharedInstance().connectWithFrameBundleName("sampleframes_hq", withBatteryChargePercentage: 42)
    }

    func FLIROneSDKDidConnect() {
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveBlendedMSXRGBA8888Image msxImage: NSData!, imageSize size: CGSize) {
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveRadiometricData radiometricData: NSData!, imageSize size: CGSize) {
    }
}
