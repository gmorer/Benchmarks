#!/usr/bin/env node

const https = require('https')

const USAGE = './test.js [URI] [REGEX]'

const main = () => {
	if (process.argv.length < 4) return console.error("invalid usage")
	try {
	const reg = new RegExp(process.argv[3])
	https.get(process.argv[2], res => {
		let body = ''
		let headers = res.headers
		res.on('data', chunk => body += chunk);
		res.on('end', () => console.log(body.match(reg)[1]))
	})
	} catch (e) { console.error(e.msg) }
}

main();
