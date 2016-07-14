import UIKit

let sizeOfMeasurment = sizeof(UInt16)
let hundredthsOfKelvinToFarenheitDegrees: Float = 0.018
let absoluteZeroInFarhenheit: Float = -459.67
let halfOfFLIRPeriod: NSTimeInterval = 0.05555555555556
let flip = CGAffineTransformMakeScale(1, -1)
class ViewController: UIViewController, FLIROneSDKImageReceiverDelegate, FLIROneSDKStreamManagerDelegate {

    @IBOutlet weak private var imageView: UIImageView!
    @IBOutlet weak private var maxTemperatureLabel: UILabel!
    @IBOutlet weak private var minTemperatureLabel: UILabel!
    @IBOutlet weak private var maxTemperatureCrosshairs: UIImageView!
    @IBOutlet weak private var minTemperatureCrosshairs: UIImageView!
    @IBOutlet weak private var maxTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet weak private var maxTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet weak private var minTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet weak private var minTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet weak private var fieldOfVision: UIView!
    @IBOutlet weak private var reflection: UIImageView!

    private var xScaleFactor: CGFloat = 1.0
    private var yScaleFactor: CGFloat = 1.0
    private var previousSizeOfFieldOfVision = CGSize()
    private var previousSizeOfImage = CGSize()
    private let flirDataSource = FLIRDataSource()

    override func viewDidLoad() {
        super.viewDidLoad()
        self.reflection.transform = flip
        flirDataSource.imageOptions = FLIRImageOptions(rawValue: (FLIRImageOptions.BlendedMSXRGBA8888.rawValue) | (FLIRImageOptions.RadiometricKelvinx100.rawValue))
        flirDataSource.didConnectClosure = {
            self.flirDataSource.palette = .Iron
        }
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveBlendedMSXRGBA8888Image msxImage: NSData!, imageSize size: CGSize) {
        let image = FLIROneSDKUIImage(format: FLIROneSDKImageOptions.BlendedMSXRGBA8888Image, andData: msxImage, andSize: size)
        dispatch_async(dispatch_get_main_queue()) {
            self.imageView.image = image;
            self.reflection.image = image;
        }
    }

    func FLIROneSDKDelegateManager(delegateManager: NSObject!, didReceiveRadiometricData radiometricData: NSData!, imageSize size: CGSize) {
        var maxTemperature = UInt16()
        var minTemperature = UInt16.max
        var memoryPositionOfMaximumTemperature = 0
        var memoryPositionOfMinimumTemperature = 0
        var currentMemoryPosition = 0

        radiometricData.enumerateByteRangesUsingBlock {(bytes: UnsafePointer<()>, range: NSRange, stop: UnsafeMutablePointer<ObjCBool>) in
            while currentMemoryPosition < range.length - range.location {
                let integer = UnsafePointer<UInt16>(bytes + currentMemoryPosition)
                let temperature = integer.memory
                if temperature > maxTemperature {
                    maxTemperature = temperature
                    memoryPositionOfMaximumTemperature = currentMemoryPosition
                }
                if temperature < minTemperature {
                    minTemperature = temperature
                    memoryPositionOfMinimumTemperature = currentMemoryPosition
                }
                currentMemoryPosition += sizeOfMeasurment
            }
        }

        let sizeFloor = Int(round(size.width))
        let coordinatesOfMaxTemperature = rowMajorPositionToCoordinates(memoryPositionOfMaximumTemperature / sizeOfMeasurment, rowCount: sizeFloor)
        let scaledCoordinatesOfMaxTemperature = scaleCoordinates(coordinatesOfMaxTemperature, toSize: size)
        let coordinatesOfMinTemperature = rowMajorPositionToCoordinates(memoryPositionOfMinimumTemperature / sizeOfMeasurment, rowCount: sizeFloor)
        let scaledCoordinatesOfMinTemperature = scaleCoordinates(coordinatesOfMinTemperature, toSize: size)
        dispatch_async(dispatch_get_main_queue()) {
            self.maxTemperatureCrosshairsTargetCoordinates(scaledCoordinatesOfMaxTemperature)
            self.minTemperatureCrosshairsTargetCoordinates(scaledCoordinatesOfMinTemperature)
            self.maxTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(maxTemperature)) °F";
            self.minTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(minTemperature)) °F";
            UIView.animateWithDuration(halfOfFLIRPeriod) {
                self.view.layoutIfNeeded()
            }
        }
    }

    private func scaleCoordinates(coordinates: CGPoint, toSize size: CGSize) -> CGPoint {
        updateScalingForSize(size)
        return CGPoint(x: coordinates.x * xScaleFactor, y: coordinates.y * yScaleFactor)
    }

    private func updateScalingForSize(size: CGSize) {
        let sizeOfFieldOfVision = fieldOfVision.frame.size
        if size == previousSizeOfImage && sizeOfFieldOfVision == previousSizeOfFieldOfVision {
            return
        }
        xScaleFactor = sizeOfFieldOfVision.width / size.width
        yScaleFactor = sizeOfFieldOfVision.height / size.height
        previousSizeOfImage = size
        previousSizeOfFieldOfVision = sizeOfFieldOfVision
    }

    private func maxTemperatureCrosshairsTargetCoordinates(coordinates: CGPoint) {
        self.maxTemperatureCrosshairsX.constant = coordinates.x
        self.maxTemperatureCrosshairsY.constant = coordinates.y
    }

    private func minTemperatureCrosshairsTargetCoordinates(coordinates: CGPoint) {
        self.minTemperatureCrosshairsX.constant = coordinates.x
        self.minTemperatureCrosshairsY.constant = coordinates.y
    }

    func rowMajorPositionToCoordinates(position: Int, rowCount: Int) -> CGPoint {
        let x = position % rowCount
        let y = position / rowCount
        return CGPoint(x: CGFloat(x), y: CGFloat(y))
    }

    func hundredthsOfKelvinInFahrenheit(hundredthsOfKelvin: UInt16) -> Float {
        return (Float(hundredthsOfKelvin) * hundredthsOfKelvinToFarenheitDegrees + absoluteZeroInFarhenheit)
    }
}

