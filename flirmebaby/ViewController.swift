import UIKit

let sizeOfMeasurment = MemoryLayout<UInt16>.size
let hundredthsOfKelvinToFarenheitDegrees: Float = 0.018
let absoluteZeroInFarhenheit: Float = -459.67
let halfOfFLIRPeriod: TimeInterval = 0.05555555555556
let verticalFlip = CGAffineTransform(scaleX: 1, y: -1)
let horizontalFlip = CGAffineTransform(scaleX: -1, y: 1)
let upsideDown = CGAffineTransform(rotationAngle: -CGFloat.pi)
let rightSideUp = CGAffineTransform(rotationAngle: 0)

class ViewController: UIViewController {

    @IBOutlet private var imageView: UIImageView!
    @IBOutlet private var maxTemperatureLabel: UILabel!
    @IBOutlet private var minTemperatureLabel: UILabel!
    @IBOutlet private var maxTemperatureCrosshairs: UIImageView!
    @IBOutlet private var minTemperatureCrosshairs: UIImageView!
    @IBOutlet private var maxTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet private var maxTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet private var minTemperatureCrosshairsX: NSLayoutConstraint!
    @IBOutlet private var minTemperatureCrosshairsY: NSLayoutConstraint!
    @IBOutlet private var fieldOfVision: UIView!
    @IBOutlet private var reflection: UIImageView!
    @IBOutlet private var disconnectedView: UIVisualEffectView!

    private var xScaleFactor: CGFloat = 1.0
    private var yScaleFactor: CGFloat = 1.0
    private var previousSizeOfFieldOfVision = CGSize()
    private var previousSizeOfImage = CGSize()
    private var flirDataSource: FLIRDataSource? {
        didSet {
            flirDataSource?.imageOptions = [.blendedMSXRGBA8888, .radiometricKelvinx100]
            flirDataSource?.didConnectClosure = {
                self.flirDataSource?.palette = .iron
                DispatchQueue.main.async {
                    self.disconnectedView.isHidden = true
                    self.orientImage()
                }
            }
            flirDataSource?.didDisconnectClosure = {
                DispatchQueue.main.async {
                    self.disconnectedView.isHidden = false
                    let philly = UIImage(named: "Philadelphia")
                    self.imageView.image = philly
                    self.reflection.image = philly
                    self.maxTemperatureLabel.text = "Hot!"
                    self.minTemperatureLabel.text = "Brr!"

                }
            }
            flirDataSource?.didReceiveImageClosure = { image, size in
                DispatchQueue.main.async {
                    self.imageView.image = image
                    self.reflection.image = image
                }
            }
            flirDataSource?.didReceiveDataClosure = { data, size in
                self.seekHotAndCold(data as Data, imageSize: size)
            }
        }
    }
    override var supportedInterfaceOrientations: UIInterfaceOrientationMask {
        return [.portrait, .portraitUpsideDown]
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        flirDataSource = FLIRDataSource()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        orientImage()
    }

    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        super.viewWillTransition(to: size, with: coordinator)
        coordinator.animate(alongsideTransition: { _ in
            self.orientImage()
        }, completion: nil)
    }

    @IBAction func showDemo(_ sender: UIButton) {
        flirDataSource?.showDemo()
    }

    private func orientImage() {
        switch UIDevice.current.orientation {
        case .portrait, .faceUp, .faceDown:
            self.fieldOfVision.transform = rightSideUp
            self.reflection.transform = verticalFlip
        case .portraitUpsideDown:
            guard let flirDataSource = flirDataSource else {
                break
            }
            let rotationUnnecessary = flirDataSource.isDemoShown || !(self.disconnectedView.isHidden)
            self.fieldOfVision.transform = rotationUnnecessary ? rightSideUp : upsideDown
            self.reflection.transform = rotationUnnecessary ? verticalFlip : horizontalFlip
        default: break
        }
    }

    func seekHotAndCold(_ radiometricData: Data!, imageSize size: CGSize) {
        var maxTemperature = UInt16()
        var minTemperature = UInt16.max
        var memoryPositionOfMaximumTemperature = 0
        var memoryPositionOfMinimumTemperature = 0
        var currentMemoryPosition = 0
        let length = radiometricData.count / MemoryLayout<UInt8>.size
        radiometricData.enumerateBytes {(buffer: UnsafeBufferPointer<UInt8>, _: Data.Index, _: inout Bool) in
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
            self.maxTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(maxTemperature)) °F"
            self.minTemperatureLabel.text = "\(self.hundredthsOfKelvinInFahrenheit(minTemperature)) °F"
            UIView.animate(withDuration: halfOfFLIRPeriod, animations: {
                self.view.layoutIfNeeded()
            })
        }
    }

    private func scaleCoordinates(_ coordinates: CGPoint, toSize size: CGSize) -> CGPoint {
        updateScalingForSize(size)
        return CGPoint(x: coordinates.x * xScaleFactor, y: coordinates.y * yScaleFactor)
    }

    private func updateScalingForSize(_ size: CGSize) {
        let sizeOfFieldOfVision = fieldOfVision.frame.size
        if size == previousSizeOfImage && sizeOfFieldOfVision == previousSizeOfFieldOfVision {
            return
        }
        xScaleFactor = sizeOfFieldOfVision.width / size.width
        yScaleFactor = sizeOfFieldOfVision.height / size.height
        previousSizeOfImage = size
        previousSizeOfFieldOfVision = sizeOfFieldOfVision
    }

    private func maxTemperatureCrosshairsTargetCoordinates(_ coordinates: CGPoint) {
        self.maxTemperatureCrosshairsX.constant = coordinates.x
        self.maxTemperatureCrosshairsY.constant = coordinates.y
    }

    private func minTemperatureCrosshairsTargetCoordinates(_ coordinates: CGPoint) {
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
