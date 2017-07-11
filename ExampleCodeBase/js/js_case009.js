$.ajax({
		type: "POST",
		url: "~/pythoncode.py",
		data: { param: text}
		}).done(function( o ) {
		 // do something
		});

