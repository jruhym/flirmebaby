import Foundation
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
