var app = {
	
	initialize: function() {
		document.addEventListener('deviceready', this.onDeviceReady, false);
	},
	onDeviceReady: function() {
		var P1Text = document.getElementById('P1');
		var P2Text = document.getElementById('P2');
		var debug_out = document.getElementById('debug_out');
//		var on = document.getElementById('on');
//		var off = document.getElementById('off');
		var str = '';
		var buffer = [];
		var graph_buffer_p1 = [];
		var graph_buffer_p2 = [];
		var value = 0;
		var pm25_serial = 0;
		var pm10_serial = 0;
		var checksum_is = 0;
		var serial_pos = 0;
		var checksum_ok = 0;

		var errorCallback = function(message) {
			alert('Error: ' + message);
		};
		// request permission first
		serial.requestPermission(
			// if user grants permission
			function(successMessage) {
                // open serial port
                serial.open(
                    {baudRate: 9600},
                    // if port is succesfully opened
                    function(successMessage) {
                        // register the read callback

							serial.registerReadCallback(
								function success(data){
									// decode the received message
									var view = new Uint8Array(data);
									setTimeout(function(){
										if(view.length >= 1) {
											for(var i=0; i < view.length; i++) {
												buffer.push(view[i]);
											}
										}
										while (buffer.length > 0) {
											value = buffer.shift();
//											console.log(value);
											switch (serial_pos) {
												case 0: if (value != 170) { serial_pos = -1; }; break;
												case 1: if (value != 192) { serial_pos = -1; }; break;
												case 2: pm25_serial = value; checksum_is = value; break;
												case 3: pm25_serial += (value << 8); checksum_is += value; break;
												case 4: pm10_serial = value; checksum_is += value; break;
												case 5: pm10_serial += (value << 8); checksum_is += value; break;
												case 6: checksum_is += value; break;
												case 7: checksum_is += value; break;
												case 8:
													if (value == (checksum_is % 256)) { checksum_ok = 1; } else { serial_pos = -1; }; break;
												case 9: if (value != 171) { serial_pos = -1; }; break;
											}
											serial_pos++;
											if (serial_pos == 10 && checksum_ok == 1) {
												if ((! isNaN(pm10_serial)) && (! isNaN(pm25_serial))) {
													P1Text.innerText = (pm10_serial/10).toFixed(1);
													P2Text.innerText = (pm25_serial/10).toFixed(1);
													while (graph_buffer_p1.length >= 500) graph_buffer_p1.shift();
													while (graph_buffer_p2.length >= 500) graph_buffer_p2.shift();
													graph_buffer_p1.push(pm10_serial/10);
													graph_buffer_p2.push(pm25_serial/10);
												}
												serial_pos = 0; checksum_ok = 0; pm10_serial = 0.0; pm25_serial = 0.0; checksum_is = 0;
											}
										}
//										debug_out.innerText = graph_buffer_p1.length;
										var canvas = document.getElementById("graph");
										var canvas_width = Math.min(document.getElementById("value_out").offsetWidth,500);
										canvas.style.width = canvas_width+"px";

										var graph_offset = Math.max(0,(graph_buffer_p1.length-canvas.width))
										console.log("Buffer length: "+graph_buffer_p1.length+", Canvas width (calc): "+canvas_width+", Canvas width: "+canvas.width+", Canvas height: "+canvas.height+", Offset: "+graph_offset);

										if (canvas.getContext) {

											var ctx = canvas.getContext("2d");
											
											ctx.clearRect(0,0,canvas.width, canvas.height);
											
											ctx.strokeStyle = "gray";
											ctx.beginPath();
											ctx.moveTo(0,0);
											ctx.lineTo(canvas.width-1,0);
											ctx.lineTo(canvas.width-1,149);
											ctx.lineTo(0,149);
											ctx.lineTo(0,0);
											ctx.stroke();

											ctx.beginPath();
											ctx.moveTo(0,100);
											ctx.lineTo(canvas.width-1,100);
											ctx.stroke();

											ctx.beginPath();
											ctx.moveTo(0,50);
											ctx.lineTo(canvas.width-1,50);
											ctx.stroke();

											var max_p1 = 150;
											for (var i=graph_offset; i < graph_buffer_p1.length; i++) {
												if (graph_buffer_p1[i] > max_p1) { max_p1 = graph_buffer_p1[i]; }
											}

											scaling = (Math.floor(max_p1/100)+1)*100/150;
											console.log(max_p1+", "+scaling);

											ctx.strokeStyle = "rgb(200,0,0)";
											ctx.beginPath();
											ctx.moveTo(0,150-(graph_buffer_p1[graph_offset]/scaling))
											for (var i=graph_offset; i < graph_buffer_p1.length; i++) {
												ctx.lineTo(i-graph_offset, 150-Math.round(graph_buffer_p1[i]/scaling));
												ctx.stroke();
											}

											ctx.strokeStyle = "rgb(0, 0, 200)";
											ctx.beginPath();
											ctx.moveTo(0,150-(graph_buffer_p2[graph_offset]/scaling))
											for (var i=graph_offset; i < graph_buffer_p2.length; i++) {
												ctx.lineTo(i-graph_offset, 150-Math.round(graph_buffer_p2[i]/scaling));
												ctx.stroke();
											}
										}
									},200);
								},
								// error attaching the callback
								errorCallback
							);
					},
					// error opening the port
					errorCallback
				);
			},
			// user does not grant permission
			errorCallback
		);

/*		on.onclick = function() {
			console.log('click');
			if (open) serial.write('1');
		};
		off.onclick = function() {
			if (open) serial.write('0');
		} */
	}
};

app.initialize();
