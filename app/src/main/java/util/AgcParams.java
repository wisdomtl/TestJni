package util;

public class AgcParams {
    private short targetLevelDbfs;
    private short compressionGainDb;
    private boolean limiterEnable;
    private long fs;

    public short getTargetLevelDbfs() {
        return targetLevelDbfs;
    }

    public void setTargetLevelDbfs(short targetLevelDbfs) {
        this.targetLevelDbfs = targetLevelDbfs;
    }

    public short getCompressionGainDb() {
        return compressionGainDb;
    }

    public void setCompressionGainDb(short compressionGainDb) {
        this.compressionGainDb = compressionGainDb;
    }

    public boolean getLimiterEnable() {
        return limiterEnable;
    }

    public void setLimiterEnable(boolean limiterEnable) {
        this.limiterEnable = limiterEnable;
    }

    public long getFs() {
        return fs;
    }

    public void setFs(long fs) {
        this.fs = fs;
    }
}
