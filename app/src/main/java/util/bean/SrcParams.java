package util.bean;

public class SrcParams {
    private int inSampleRate;
    private int outSampleRate;
    private int channel;
    private int quality;

    public int getInSampleRate() {
        return inSampleRate;
    }

    public void setInSampleRate(int inSampleRate) {
        this.inSampleRate = inSampleRate;
    }

    public int getOutSampleRate() {
        return outSampleRate;
    }

    public void setOutSampleRate(int outSampleRate) {
        this.outSampleRate = outSampleRate;
    }

    public int getChannel() {
        return channel;
    }

    public void setChannel(int channel) {
        this.channel = channel;
    }

    public int getQuality() {
        return quality;
    }

    public void setQuality(int quality) {
        this.quality = quality;
    }
}
