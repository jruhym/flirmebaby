import UIKit

let sizeOfMeasurment = MemoryLayout<UInt16>.size
let hundredthsOfKelvinToFarenheitDegrees: Float = 0.018
let absoluteZeroInFarhenheit: Float = -459.67
let halfOfFLIRPeriod: TimeInterval = 0.05555555555556
let flip = CGAffineTransform(scaleX: 1, y: -1)
let upsideDown = CGAffineTransform(rotationAngle: -CGFloat.pi)
let rightSideUp = CGAffineTransform(rotationAngle: 0)

class ViewController: UIViewController {

    @IBOutlet weak fileprivate var imageView: UIImageView!
    @IBOutlet weak fileprivate var maxTemperatureLabel: UILabel!
    @IBOutlet weak fileprivate var minTemperatureLabel: UILabel!
    @IBOutlet weak fileprivate var maxTemperatureCrosshairs: UIImageView!
    @IBOutlet weak fileprivate var minTemperatureCrosshairs: UIImageView!
    @IBOutlet weak fileprivate var maxTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet weak fileprivate var maxTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet weak fileprivate var minTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet weak fileprivate var minTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet weak fileprivate var fieldOfVision: UIView!
    @IBOutlet weak fileprivate var reflection: UIImageView!
    @IBOutlet fileprivate var viewsWhenDisconnected: [UIView]!

    fileprivate var xScaleFactor: CGFloat = 1.0
    fileprivate var yScaleFactor: CGFloat = 1.0
    fileprivate var previousSizeOfFieldOfVision = CGSize()
    fileprivate var previousSizeOfImage = CGSize()
    fileprivate weak var flirDataSource: FLIRDataSource? {
        didSet {
            flirDataSource?.imageOptions = [.blendedMSXRGBA8888, .radiometricKelvinx100]
            flirDataSource?.didConnectClosure = {
                self.flirDataSource?.palette = .Iron
                DispatchQueue.main.async {
                    self.orientImage()
                    for view in self.viewsWhenDisconnected {
                        view.isHidden = true
                    }
                }
            }
            flirDataSource?.didDisconnectClosure = {
                DispatchQueue.main.async {
                    for view in self.viewsWhenDisconnected {
                        view.isHidden = false
                    }
                }
            }
            flirDataSource?.didReceiveImageClosure = { image, size in
                DispatchQueue.main.async {
                    self.imageView.image = image;
                    self.reflection.image = image;
                }
            }
            flirDataSource?.didReceiveDataClosure = { data, size in
                self.seekHotAndCold(data as Data, imageSize: size)
            }
        }
    }
    override var supportedInterfaceOrientations : UIInterfaceOrientationMask {
        return [.portrait, .portraitUpsideDown]
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        reflection.transform = flip
        flirDataSource = FLIRDataSource()
    }

    @IBAction func showDemo(_ sender: UIButton) {
        flirDataSource?.showDemo()
    }

    fileprivate func orientImage() {
        switch UIDevice.current.orientation {
        case .portrait:
            self.fieldOfVision.transform = rightSideUp
            self.reflection.transform = upsideDown
        case .portraitUpsideDown:
            guard let flirDataSource = flirDataSource else {
                break
            }
            let rotationUnnecessary = flirDataSource.isDemoShown
            self.fieldOfVision.transform = rotationUnnecessary ? rightSideUp : upsideDown
            self.reflection.transform = rotationUnnecessary ? upsideDown : rightSideUp
        default: break
        }
    }

    func seekHotAndCold(_ radiometricData: Data!, imageSize size: CGSize) {
        var maxTemperature = UInt16()
        var minTemperature = UInt16.max
        var memoryPositionOfMaximumTemperature = 0
        var memoryPositionOfMinimumTemperature = 0
        var currentMemoryPosition = 0

        radiometricData.enumerateBytes {(buffer: UnsafeBufferPointer<UInt8>, length: Data.Index, stop: inout Bool) in
            while currentMemoryPosition < length {
                guard let baseAddress = buffer.baseAddress else {
                    return
                }
                let integer = UnsafeRawPointer(baseAddress + currentMemoryPosition)
                let temperature = integer.load(as: UInt16.self)
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
        DispatchQueue.main.async {
            self.maxTemperatureCrosshairsTargetCoordinates(scaledCoordinatesOfMaxTemperature)
            self.minTemperatureCrosshairsTargetCoordinates(scaledCoordinatesOfMinTemperature)
            self.maxTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(maxTemperature)) °F";
            self.minTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(minTemperature)) °F";
            UIView.animate(withDuration: halfOfFLIRPeriod, animations: {
                self.view.layoutIfNeeded()
            }) 
        }
    }

    fileprivate func scaleCoordinates(_ coordinates: CGPoint, toSize size: CGSize) -> CGPoint {
        updateScalingForSize(size)
        return CGPoint(x: coordinates.x * xScaleFactor, y: coordinates.y * yScaleFactor)
    }

    fileprivate func updateScalingForSize(_ size: CGSize) {
        let sizeOfFieldOfVision = fieldOfVision.frame.size
        if size == previousSizeOfImage && sizeOfFieldOfVision == previousSizeOfFieldOfVision {
            return
        }
        xScaleFactor = sizeOfFieldOfVision.width / size.width
        yScaleFactor = sizeOfFieldOfVision.height / size.height
        previousSizeOfImage = size
        previousSizeOfFieldOfVision = sizeOfFieldOfVision
    }

    fileprivate func maxTemperatureCrosshairsTargetCoordinates(_ coordinates: CGPoint) {
        self.maxTemperatureCrosshairsX.constant = coordinates.x
        self.maxTemperatureCrosshairsY.constant = coordinates.y
    }

    fileprivate func minTemperatureCrosshairsTargetCoordinates(_ coordinates: CGPoint) {
        self.minTemperatureCrosshairsX.constant = coordinates.x
        self.minTemperatureCrosshairsY.constant = coordinates.y
    }

    func rowMajorPositionToCoordinates(_ position: Int, rowCount: Int) -> CGPoint {
        let x = position % rowCount
        let y = position / rowCount
        return CGPoint(x: CGFloat(x), y: CGFloat(y))
    }

    func hundredthsOfKelvinInFahrenheit(_ hundredthsOfKelvin: UInt16) -> Float {
        return (Float(hundredthsOfKelvin) * hundredthsOfKelvinToFarenheitDegrees + absoluteZeroInFarhenheit)
    }
}

