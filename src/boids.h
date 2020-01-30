class boid {
	public:
		float px, py, pz;
		float vx, vy, vz;
		boid(){}
		boid(float pxin, float pyin, float pzin, float vxin, float vyin, float vzin){
			px = pxin;
			py = pyin;
			pz = pzin;
			vx = vxin;
			vy = vyin;
			vz = vzin;
		}
};