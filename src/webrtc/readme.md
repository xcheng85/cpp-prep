web-based interactive streaming
solution for graphics-intensive workloads

hardware encoding or decoding of real-time streams

Remote interactive visualization of large datasets for scientific industries

WebRTC is a modern set of protocols designed for secure low-latency streaming of video,
audio, and arbitrary data

Modern web browsers and platforms can
decode H.264 video streams without any extra plugins

WebRTC includes the following key features:
Native web browser support
Hardware-accelerated formats
Built-in encryption by default
Peer-to-peer communication
Ability to traverse NAT gateways and firewalls

NVIDIA hardware video encoder

the streaming resolution is
1920x1080 (1080p), and NVENC is encoding to H.264 at 8 Mbps, and noVNC is pushing PNG
images composited on an HTML5 canvas element over a WebSocket.

WebRTC is less effective for latency-tolerant streaming like pre-recorded or rendered
video content delivery


DTLS: TLS + UDP, The certificate
exchange and TLS handshake are all handled by the browser implementation of WebRTC.



Exchange ice candidates between two peers

RTCPeerConnection
create peers1, peer2

SDP: exchange, setLocal/remote sdp
STUN. discover external ip address
signaling
TURN: opensource coTurn project, authentication
Turn Web Api: generate RTCPeerConeection configuguration

peerconnection config
createOffersdp,
createAnswserSDP
exchange ice candidatess
test ice candidates
connect

ximagesrc captures the X11 display from a Unix socket at 60 fps into an RGB-format
buffer.
videoconvert converts the RGB buffer to NVENC-compatible format.
nvh264enc encodes the buffer to H.264 on a GPU using NVENC.
rtph26pay creates an RTP packet payload sent over a peer connection.

Data channels use the Stream Control Transmission
Protocol (SCTP)
(https://web.archive.org/web/20210310083658/https://tools.ietf.org/html/draft-ietf-rtcweb-data-channel-
13)
to transport data over the peer connection. Any data can be sent over this channel, and its
interface is similar to that of a WebSocket.

browser passed to the X11 server, glfw/sdl could capture it, Xlib library

Mouse events are sent to the X11 screen as absolute position or as relative motion. By
calculating the browser client viewport, video scaling factor, and page offsets, you can send
the translated mouse event to the X11 screen

RTC data channel can also be used to send command and
control messages

dynamically change the bitrate(https://github.com/webrtc/samples/blob/gh-pages/src/content/peerconnection/bandwidth/js/main.js), or toggle the mouse pointer visibility

RTCRtpSender control the bitrate parameters

angular side: 

The web app fetches the TURN
server credentials, connects to the signaling server, establishes a peer connection, and
captures user inputs

debugging:
RTCPeerConnection statistics by opening the
chrome://webrtc-internals URI

Peer connection type determined by ICE
Number of packets received and lost
Connection latency
Jitter buffer
performance
Video bitrate
Video frame rate
stats graph

Sources of Latency: 

1. renderer
2. network 
3. client decode latency
Video googCurrentDelayMs
Video googJitterBufferMs
Video googFrameRateOutput

sending server is experiencing high CPU load, this can also slow down the pipeline and
introduce latency.

The chrome://webrtc-internals page is one of the
best resources for tracing this handshake

transceiver added: RTCRtpTransceiver describes a permanent pairing of an RTCRtpSender and an RTCRtpReceiver

  peer_connection_factory_ = webrtc::CreatePeerConnectionFactory(
      nullptr /* network_thread */, nullptr /* worker_thread */,
      nullptr /* signaling_thread */, nullptr /* default_adm */,
      webrtc::CreateBuiltinAudioEncoderFactory(),
      webrtc::CreateBuiltinAudioDecoderFactory(),
      webrtc::CreateBuiltinExternalVideoEncoderFactory(),/* webrtc::CreateBuiltinVideoEncoderFactory(),*/
      webrtc::CreateBuiltinVideoDecoderFactory(), nullptr /* audio_mixer */,
      nullptr /* audio_processing */);